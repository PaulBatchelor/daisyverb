#include "reverbsc.h"
#include "dcblock.h"
#include "daisy.h"
#include "seed.h"
#include "patch.h"

static dsy_reverbsc_t verb;
static dsy_dcblock_t dcblock[2];
static float drylevel, send;

static void callback(float *in, float *out, size_t size)
{
    float dryL, dryR, wetL, wetR, sendL, sendR;
    size_t i;
    for (i = 0; i < size; i += 2) {
        verb.feedback = 0.15f + (dsy_adc_get_float(DSY_PATCH_KNOB_1) * 0.85f);
        verb.lpfreq = 200.0f + (dsy_adc_get_float(DSY_PATCH_KNOB_2) * 18000.0f);
        drylevel = dsy_adc_get_float(DSY_PATCH_KNOB_3);
        send = dsy_adc_get_float(DSY_PATCH_KNOB_4);
        dryL = in[i];
        dryR = in[i+1];
        sendL = dryL * send;
        sendR = dryR * send;
        dsy_reverbsc_process(&verb, &sendL, &sendR, &wetL, &wetR);
        wetL = dsy_dcblock_process(&dcblock[0], wetL);
        wetR = dsy_dcblock_process(&dcblock[1], wetR);
        out[i] = (dryL * drylevel) + wetL;
        out[i + 1] = (dryR * drylevel) + wetR;
    }
}

int main(void)
{
    daisy_patch_init();
    dsy_reverbsc_init(&verb, DSY_AUDIO_SAMPLE_RATE);
    dsy_dcblock_init(&dcblock[0], DSY_AUDIO_SAMPLE_RATE);
    dsy_dcblock_init(&dcblock[1], DSY_AUDIO_SAMPLE_RATE);
    dsy_audio_set_callback(DSY_AUDIO_INTERNAL, callback);
    dsy_adc_start();
    dsy_audio_start(DSY_AUDIO_INTERNAL);
    while(1) {}
}

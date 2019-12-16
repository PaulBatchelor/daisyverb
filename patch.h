#ifndef PATCH_H
#define PATCH_H
/* Order of ADC Channels for accessing adc.h */
enum {
	DSY_PATCH_KNOB_1,
	DSY_PATCH_KNOB_2,
	DSY_PATCH_KNOB_3,
	DSY_PATCH_KNOB_4,
	DSY_PATCH_CV_1,
	DSY_PATCH_CV_2,
	DSY_PATCH_CV_3,
	DSY_PATCH_CV_4,
	DSY_PATCH_CV_LAST
};

void daisy_patch_init(void);
#endif

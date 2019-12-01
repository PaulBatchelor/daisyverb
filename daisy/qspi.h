#ifndef DSY_QSPI
#define DSY_QSPI

#ifdef __cplusplus
extern "C" {
#endif

/* Error codes */
#define DSY_MEMORY_OK ((uint32_t)0x00)
#define DSY_MEMORY_ERROR ((uint32_t)0x01)

typedef enum {
    DSY_QSPI_PIN_IO0,
    DSY_QSPI_PIN_IO1,
    DSY_QSPI_PIN_IO2,
    DSY_QSPI_PIN_IO3,
    DSY_QSPI_PIN_CLK,
    DSY_QSPI_PIN_NCS,
    DSY_QSPI_PIN_LAST,
} dsy_qspi_pin;

typedef enum {
    DSY_QSPI_MODE_DSY_MEMORY_MAPPED,
    DSY_QSPI_MODE_INDIRECT_POLLING,
    DSY_QSPI_MODE_LAST,
} dsy_qspi_mode;

typedef enum {
    DSY_QSPI_DEVICE_IS25LP080D,
    DSY_QSPI_DEVICE_IS25LP064A,
    DSY_QSPI_DEVICE_LAST,
} dsy_qspi_device;

typedef struct {
    dsy_qspi_mode mode;
    dsy_qspi_device device;
    dsy_gpio_pin pin_config[DSY_QSPI_PIN_LAST];
} dsy_qspi_handle_t;

int dsy_qspi_init(dsy_qspi_handle_t* hqspi);
int dsy_qspi_deinit(void);
int dsy_qspi_writepage(uint32_t adr, uint32_t sz, uint8_t* buf);
int dsy_qspi_write(uint32_t address, uint32_t size, uint8_t* buffer);
int dsy_qspi_erase(uint32_t start_adr, uint32_t end_adr);
int dsy_qspi_erasesector(uint32_t addr);

#ifdef __cplusplus
}
#endif

#endif

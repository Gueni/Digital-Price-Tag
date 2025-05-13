PROJECT_NAME := price_tag
TARGETS := nrf52832_xxaa

SDK_ROOT := ../nRF5_SDK_17.1.0_ddde560
PROJ_DIR := .

BOARD := pca10040
OUTPUT_DIRECTORY := _build

TEMPLATE_PATH := $(SDK_ROOT)/components/toolchain/gcc

C_SOURCE_FILES += \
  $(PROJ_DIR)/src/main.c \
  $(PROJ_DIR)/src/ble_price_service.c \
  $(PROJ_DIR)/src/eink_driver.c

INC_FOLDERS += -I$(PROJ_DIR)/include \
               -I$(SDK_ROOT)/components \
               -I$(SDK_ROOT)/components/ble/common \
               -I$(SDK_ROOT)/components/ble/ble_services \
               -I$(SDK_ROOT)/components/softdevice/s132/headers

CFLAGS += -DNRF52832_XXAA -DBOARD_PCA10040 -DSOFTDEVICE_PRESENT -D__HEAP_SIZE=2048 -D__STACK_SIZE=2048
LDFLAGS += -L$(SDK_ROOT)/components/toolchain/gcc -T$(TEMPLATE_PATH)/nrf52.ld

all:
	make -C $(TEMPLATE_PATH) -f Makefile.common \
		PROJECT_NAME=$(PROJECT_NAME) \
		OUTPUT_DIRECTORY=$(OUTPUT_DIRECTORY) \
		SDK_ROOT=$(SDK_ROOT) \
		C_SOURCE_FILES="$(C_SOURCE_FILES)" \
		INC_FOLDERS="$(INC_FOLDERS)" \
		CFLAGS="$(CFLAGS)" \
		LDFLAGS="$(LDFLAGS)" \
		TARGETS="$(TARGETS)"

clean:
	rm -rf _build
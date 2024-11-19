#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/reboot.h>
#include "heartbeat.h"
#include <zephyr/autoconf.h> /* generated, for CONFIG_SYS_CLOCK_TICKS_PER_SEC */

#define LED0_NODE DT_ALIAS(led0)

// Timing constants in milliseconds
#define HEARTBEAT_PULSE     100
#define BETWEEN_BEATS     700
#define NUM_BEATS         10

void heartbeat(void)
{
    const struct gpio_dt_spec led_dev = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
    int ret;

    if (!gpio_is_ready_dt(&led_dev)) {
        printk("Failed to bind LED device\n");
        return;
    }

    ret = gpio_pin_configure_dt(&led_dev, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Failed to configure LED GPIO pin\n");
		return;
	}

    uint32_t count = 0;
    while (count < NUM_BEATS) {
        printk("Heartbeat: %u\n", count++);
        
        // First pulse
        gpio_pin_set_dt(&led_dev, 1);
        k_sleep(K_MSEC(HEARTBEAT_PULSE));
        gpio_pin_set_dt(&led_dev, 0);
        k_sleep(K_MSEC(HEARTBEAT_PULSE));
        
        // Second pulse
        gpio_pin_set_dt(&led_dev, 1);
        k_sleep(K_MSEC(HEARTBEAT_PULSE));
        gpio_pin_set_dt(&led_dev, 0);
        
        // Pause between beats
        k_sleep(K_MSEC(BETWEEN_BEATS));
    }

    printk("Resetting system...\n");
    k_sleep(K_MSEC(100));
    sys_reboot(SYS_REBOOT_COLD);
}
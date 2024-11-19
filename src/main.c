/**
 * @file main.c
 * @brief Main source file for the project.
 *
 * See ZEPHYR_COMMIT_HASH.txt for the Zephyr commit hash used in this project.
 * 
 * Note: The GPIO and PWM drivers must be enabled by adding CONFIG_GPIO=y and CONFIG_PWM=y in in prj.conf.
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/reboot.h>
#include <zephyr/devicetree.h>
#include <zephyr/autoconf.h>
#include "heartbeat.h"

// Compiler requires that main returns int
int main(void)
{
    printk("\n");
    printk("SimpleFOC starting up...\n");

    const struct device *pwm_dev = DEVICE_DT_GET(DT_NODELABEL(pwm2));
    
    if (!device_is_ready(pwm_dev)) {
        printk("Error: PWM device not ready\n");
        return 1;
    }

    int ret = pwm_set(pwm_dev, 1, PWM_USEC(1000), PWM_USEC(500), 0);

    if (ret) {
        printk("Error %d: failed to set PWM\n", ret);
        return ret;
    }

    printk("PWM 1kHz square wave output on PA0 should be working at this point\n");

    heartbeat();
    
    return 0;
}
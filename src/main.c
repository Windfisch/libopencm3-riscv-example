#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>


static void usart_setup(void)
{
	/* Setup GPIO pin GPIO_USART1_TX. */
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ,
		      GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART1_TX);

	/* Setup UART parameters. */
	usart_set_baudrate(USART1, 115200);
	usart_set_databits(USART1, 8);
	usart_set_stopbits(USART1, USART_STOPBITS_1);
	usart_set_mode(USART1, USART_MODE_TX);
	usart_set_parity(USART1, USART_PARITY_NONE);
	usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);

	/* Finally enable the USART. */
	usart_enable(USART1);
}

int main(void)
{
	int i;

	rcc_clock_setup_in_hsi_out_64mhz();
	rcc_periph_clock_enable(RCC_AFIO);
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOC);
	rcc_periph_clock_enable(RCC_USART1);


	gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO1 | GPIO2);

	usart_setup();

	while (1) {
		gpio_clear(GPIOC, GPIO13);
		gpio_set(GPIOA, GPIO1);
		gpio_set(GPIOA, GPIO2);
		usart_send_blocking(USART1, '1');

		for (i = 0; i < 8000000; i++) __asm__("nop");

		gpio_set(GPIOC, GPIO13);
		gpio_clear(GPIOA, GPIO1);
		gpio_set(GPIOA, GPIO2);
		usart_send_blocking(USART1, '2');
		for (i = 0; i < 8000000; i++) __asm__("nop");

		gpio_set(GPIOC, GPIO13);
		gpio_set(GPIOA, GPIO1);
		gpio_clear(GPIOA, GPIO2);
		usart_send_blocking(USART1, '3');
		for (i = 0; i < 8000000; i++) __asm__("nop");
	}

	return 0;
}

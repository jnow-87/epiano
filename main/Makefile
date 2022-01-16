bin-y := main.elf


main-y := main.o task.o led.o input.o mixer.o motor.o secret.o mcu/


.PHONY: flash
flash: $(loc_build_tree)/main.elf
	$(call cmd_run_script,avrdude -p $(mcu) -P $(CONFIG_PROG_PORT) -c $(CONFIG_PROG_TYPE) -U flash:w:$<)

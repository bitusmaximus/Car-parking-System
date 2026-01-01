# Pin Configuration – ATmega32 Car Parking System

## Microcontroller
- ATmega32 @ 16 MHz

## Pin Mapping

| Component        | ATmega32 Pin | Port | Direction |
|------------------|--------------|------|-----------|
| Entry Button     | PD0          | D    | Input     |
| Exit Button      | PD1          | D    | Input     |
| Servo Motor      | PD5 (OC1A)   | D    | Output    |
| LCD RS           | PC0          | C    | Output    |
| LCD EN           | PC1          | C    | Output    |
| LCD D4           | PC4          | C    | Output    |
| LCD D5           | PC5          | C    | Output    |
| LCD D6           | PC6          | C    | Output    |
| LCD D7           | PC7          | C    | Output    |

## Notes
- Buttons use internal pull-up resistors
- Servo powered from external 5V
- LCD runs in 4-bit mode

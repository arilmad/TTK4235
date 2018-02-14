


//Lift moves upwards and stops at nearest floor if it is not at a defined floor. 
int enter_defined_state(void);

//resetting all buttons and sensors
void initialize_lift(void);

int any_button(void);
void move_to_floor(int current_floor, int desired_floor);

int floor_order(int floor, int dir);
int prioritized_floor(int reached_floor, int dir);
int orders_ahead(int floor, int dir);
void receive_orders(void);
void clear_lamps(int floor);
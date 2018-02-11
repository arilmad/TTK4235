#include "assorted_funcs.h"
#include "channels.h"
#include "io.h"
#include "elev.h"
#include <stdlib.h>
#include <comedilib.h>

int main()
{


	initialize_lift();

	//Check if at defined state, carry on when at defined floor.
	enter_defined_state();




	return 0;
}




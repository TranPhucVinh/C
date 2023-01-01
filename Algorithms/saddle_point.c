#include <stdio.h>

int row, column;

typedef struct _saddle_point{
    int value;
    int sdr; //saddle point row
    int sdc;//saddle point column
} saddle_point;

saddle_point sp;

void set_value_for_row(int array[row][column], int row, int column){
	for (int i=0; i<column; i++){
		printf("array[%d][%d]:", row, i);
		scanf("%d", &array[row][i]);
	}
}

saddle_point find_saddle_point(int array[row][column], int row, int column){
    saddle_point _sp;
    for (int _row = 0; _row < row; _row++){
        _sp.value = array[0][0];
        _sp.sdc = 0;
        _sp.sdr = 0;
		for (int _column = 1; _column < column; _column++) {            
            if (_sp.value >= array[_row][_column]){
                _sp.value = array[_row][_column];
                _sp.sdc = _column;
                _sp.sdr = _row;
            }
        } 
        for (int _row = 0; _row < row; _row++){
            if (_sp.value < array[_row][_sp.sdc]) break;
            else {
                if (_row == (row-1)) return _sp;
            }
        }
	}
    _sp.value = -1;
    _sp.sdr = -1;
    _sp.sdc = -1;
    return _sp;
}

void main() {
	printf("enter row number:");
	scanf("%d", &row);
	printf("enter column number:");
	scanf("%d", &column);

	int array[row][column];

    //Set value for row
	for (int _row = 0; _row < row; _row++){
		set_value_for_row(array, _row, column);
	}
	
    //Display the whole array
	// for (int _row = 0; _row < row; _row++){
	// 	for (int _column = 0; _column < column; _column++) printf("array[%d][%d]: %d\n", _row, _column, array[_row][_column]);
	// }    
    sp = find_saddle_point(array, row, column);

    if ((sp.value == -1) && (sp.sdr == -1) && (sp.sdc == -1)) printf("There is no saddle point in the array\n");
    else printf("Saddle point is %d at [%d][%d]\n", sp.value, sp.sdr, sp.sdc);
}
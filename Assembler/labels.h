#ifndef LABELS_H
#define LABELS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include "../SimpleStack/data_types.h"
#include "../Common/err_codes.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

//!@def Buffer in bytes for label name in Label structure
#define LAB_BUF 100
//!@def First amount of labels in table which first time allocated
#define LAB_TABLE_INIT 50
//!@def Special value which is file into label's position at initialization step - is used to identify that no place in code was found to jump to it
#define LAB_POISON -1

//!@typedef Typedef for LabelStr struct
typedef struct LabelStr Label;

//!@typedef Typedef for values of labels
typedef int32_t label_t;

/**@brief  Label structure for jumps in code
 *
 * @param pos The address of label's position in code
 * @param first_pos First appearance of label in code -
 * if pos has LAB_POISON value then it was mentioned after jump command without address and it should be removed.
 * Then it is used for changing all labels positions following after this label to find them in byte-code after removing this label.
 * @param label The name of label
 */
struct LabelStr {
    label_t pos;
    label_t first_pos;
    char * label;
};

int LabelTableCTor(Label ** lab_table, stk_size_t lab_num);
int LabelTableDTor(Label * lab_table, stk_size_t lab_num);
int LabelTableRLC(Label * lab_table, stk_size_t lab_num);
int ReadLabels(FILE * inp_file, Label ** lab_table, size_t * lab_count);

#endif //LABELS_H

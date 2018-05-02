/*
 * DataLoader_test.c 
 * This is a unittest script for DataLoader.c
 *
*/

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

#include <stdio.h>
#include <stdlib.h>

#include "DataLoader.h"

/* Test Suite setup and cleanup functions: */

int init_suite(void)
{
  return 0;
}
int clean_suite(void)
{
  return 0;
}

/************* Test case functions ****************/


void initialize_struct_accelerometer(void) {
  Signal signal_arr[1] = {
    {.t = 10, .x=6., .y=3., .z=2.}
  };  
  CU_ASSERT_EQUAL( signal_arr[0].t , 10);
  CU_ASSERT_EQUAL( signal_arr[0].x , 6);
  CU_ASSERT_EQUAL( signal_arr[0].y , 3);
  CU_ASSERT_EQUAL( signal_arr[0].z , 2);
}


void length_of_accelerometer_struct(void){
  Signal signal_arr[2] = {
    {.t = 10, .x=6., .y=3., .z=2.},
    {.t = 10, .x=6., .y=3., .z=2.}
  };
  size_t length = sizeof(signal_arr)/sizeof(signal_arr[0]);
  CU_ASSERT_EQUAL(length , 2);
}

void readCSV_line15(void) {
  Signal signal_arr[7024];
  char filepath[20];
  strcpy(filepath, "data/AccData.csv");
  readCSV(filepath, signal_arr, 0, 7024);
  CU_ASSERT_EQUAL( signal_arr[14].t , 141);
  CU_ASSERT_EQUAL( signal_arr[14].x , 1031.25);
  CU_ASSERT_EQUAL( signal_arr[14].y , 31.25);
  CU_ASSERT_EQUAL( signal_arr[14].z , -62.5);
}

void splitCSVLine_detects_correct_number_of_columns(void) {
  char line[20];
  strcpy(line, "0,123,-22,1.44");
  int nColumns = 4;
  int nColumnsReturn;
  char *line_arr[nColumns]; 

  nColumnsReturn = splitCSVLine( line, line_arr, nColumns);

  CU_ASSERT_EQUAL( nColumnsReturn , nColumns);
}

void splitCSVLine_reads_in_correct_data(void) {
  char line[20];
  strcpy(line, "0,123,-22,1.44");
  int nColumns = 4;
  int nColumnsReturn;
  char *line_arr[nColumns]; 

  nColumnsReturn = splitCSVLine( line, line_arr, nColumns);
  printf("%s\n",line_arr[0]);
  CU_ASSERT_STRING_EQUAL( line_arr[0] , "0");
  CU_ASSERT_STRING_EQUAL( line_arr[1] , "123");
  CU_ASSERT_STRING_EQUAL( line_arr[2] , "-22");
  CU_ASSERT_STRING_EQUAL( line_arr[3] , "1.44");
}


/************* Test Runner Code goes here **************/

int main ( void ){
   CU_pSuite pSuite = NULL;
   /* initialize the CUnit test registry */
   if ( CUE_SUCCESS != CU_initialize_registry() )
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite( "csv_reader_test_suite", init_suite, clean_suite );
   if ( NULL == pSuite ) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ( (NULL == CU_add_test(pSuite, "initialize_struct_accelerometer", initialize_struct_accelerometer)) ||
        (NULL == CU_add_test(pSuite, "length_of_accelerometer_struct", length_of_accelerometer_struct)) ||
        (NULL == CU_add_test(pSuite, "readCSV_line15", readCSV_line15)) ||
        (NULL == CU_add_test(pSuite, "splitCSVLine_detects_correct_number_of_columns", splitCSVLine_detects_correct_number_of_columns)) ||
        (NULL == CU_add_test(pSuite, "splitCSVLine_reads_in_correct_data", splitCSVLine_reads_in_correct_data)) //||
      )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // Run all tests using the basic interface
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");

   /* Clean up registry and return */
   CU_cleanup_registry();
   return CU_get_error();
}

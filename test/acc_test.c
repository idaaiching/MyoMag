/*
 * acc_test.c 
 * This is a script to unittest max.c using the CUnit interface.
 * The command to run the script is the following
 * 
 * gcc -Wall -c acc.c main.c 
 * gcc -Wall -L/usr/local/lib -o acc_test acc_test.c acc.o -lcunit
 *
*/


#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
//#include "CUnit/Automated.h"
//#include "CUnit/Console.h"

#include <stdio.h>
#include <stdlib.h>

#include "acc.h"

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

void test_case_sample(void)
{
   CU_ASSERT(CU_TRUE);
   CU_ASSERT_STRING_EQUAL("string #1", "string #1");
   CU_ASSERT_NOT_EQUAL(2, -1);
   CU_ASSERT_STRING_NOT_EQUAL("string #1", "string #2");

   CU_ASSERT(CU_FALSE);
   CU_ASSERT_EQUAL(2, 3);
   CU_ASSERT_STRING_NOT_EQUAL("string #1", "string #1");
   CU_ASSERT_STRING_EQUAL("string #1", "string #2");
}



void magnitude_of_6_3_2_is_7(void) {
  int length = 1;
  DATA data_arr[1] = {
    {.t = 10, .x=6., .y=3., .z=2.}
  };
  double mag[1];
  calculateMagnitude(data_arr ,mag, 0, 1);
  CU_ASSERT_EQUAL( mag[0] , 7);
}

void initialize_struct_accelerometer(void) {
  DATA data_arr[1] = {
    {.t = 10, .x=6., .y=3., .z=2.}
  };  
  CU_ASSERT_EQUAL( data_arr[0].t , 10);
  CU_ASSERT_EQUAL( data_arr[0].x , 6);
  CU_ASSERT_EQUAL( data_arr[0].y , 3);
  CU_ASSERT_EQUAL( data_arr[0].z , 2);
}

void spatial_data_is_commutative_for_magnitude(void) {
  DATA data_arr[2] = {
    {.t = 10, .x=3., .y=6., .z=2.},
    {.t = 10, .x=6., .y=3., .z=2.}
  };
  double mag[2];
  calculateMagnitude(data_arr, mag, 0, 2);
  CU_ASSERT_EQUAL( mag[0] , mag[1]);
}

void maganitude_should_be_timeindependent(void) {
  DATA data_arr[2] = {
    {.t = 3, .x=6., .y=3., .z=2.},
    {.t = 8, .x=6., .y=3., .z=2.}
  };
  double mag[2];
  calculateMagnitude(data_arr, mag, 0, 2);
  CU_ASSERT_EQUAL( mag[0] , mag[1]);
}

void length_of_accelerometer_struct(void){
  DATA data_arr[2] = {
    {.t = 10, .x=6., .y=3., .z=2.},
    {.t = 10, .x=6., .y=3., .z=2.}
  };
  size_t length = sizeof(data_arr)/sizeof(data_arr[0]);
  CU_ASSERT_EQUAL(length , 2);
}


void readCSV_line15(void) {
  DATA data_arr[7024];
  char filepath[20];
  strcpy(filepath, "src/AccData.csv");
  readCSV(filepath, data_arr, 0, 7024);
  CU_ASSERT_EQUAL( data_arr[14].t , 141);
  CU_ASSERT_EQUAL( data_arr[14].x , 1031.25);
  CU_ASSERT_EQUAL( data_arr[14].y , 31.25);
  CU_ASSERT_EQUAL( data_arr[14].z , -62.5);
}

void read_csv_twice_should_give_same_result(void) {
  DATA data_arr[7024];
  char filepath[20];
  strcpy(filepath, "src/AccData.csv");
  readCSV(filepath, data_arr, 0, 7024);
  readCSV(filepath, data_arr, 0, 7024);
  CU_ASSERT_EQUAL( data_arr[14].t , 141);
  CU_ASSERT_EQUAL( data_arr[14].x , 1031.25);
  CU_ASSERT_EQUAL( data_arr[14].y , 31.25);
  CU_ASSERT_EQUAL( data_arr[14].z , -62.5);
}

void read_scv_in_two_steps_should_be_the_same_as_in_one_step(vois) {
  DATA a[7024];
  DATA b[7024];
  double mag_a[7024];
  double mag_b[7024];
  char filepath[20];
  strcpy(filepath, "src/AccData.csv");

  readCSV(filepath, a, 0, 7024);
  calculateMagnitude(a, mag_a, 0, 7024);

  readCSV(filepath, b, 0, 3000);
  calculateMagnitude(b, mag_b, 0, 3000);
  readCSV(filepath, b, 3000, 7024);
  calculateMagnitude(b, mag_b, 3000, 7024);

  CU_ASSERT_EQUAL( a[14].t , b[14].t);
  CU_ASSERT_EQUAL( a[14].x , b[14].x);
  CU_ASSERT_EQUAL( a[14].y , b[14].y);
  CU_ASSERT_EQUAL( a[14].z , b[14].z);
}

/************* Test Runner Code goes here **************/

int main ( void )
{
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
   if ( (NULL == CU_add_test(pSuite, "magnitude_of_6_3_2_is_7", magnitude_of_6_3_2_is_7)) ||
        (NULL == CU_add_test(pSuite, "initialize_struct_accelerometer", initialize_struct_accelerometer)) ||
        (NULL == CU_add_test(pSuite, "spatial_data_is_commutative_for_magnitude", spatial_data_is_commutative_for_magnitude)) ||
        (NULL == CU_add_test(pSuite, "maganitude_should_be_timeindependent", maganitude_should_be_timeindependent)) ||
        (NULL == CU_add_test(pSuite, "length_of_accelerometer_struct", length_of_accelerometer_struct)) ||
        (NULL == CU_add_test(pSuite, "readCSV_line15", readCSV_line15)) ||
        (NULL == CU_add_test(pSuite, "read_csv_twice_should_give_same_result", read_csv_twice_should_give_same_result)) ||
        (NULL == CU_add_test(pSuite, "read_scv_in_two_steps_should_be_the_same_as_in_one_step", read_scv_in_two_steps_should_be_the_same_as_in_one_step)) 
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
/*
   // Run all tests using the automated interface
   CU_automated_run_tests();
   CU_list_tests_to_file();

   // Run all tests using the console interface
   CU_console_run_tests();
*/
   /* Clean up registry and return */
   CU_cleanup_registry();
   return CU_get_error();
}
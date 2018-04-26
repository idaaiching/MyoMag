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
   CU_ASSERT_NOT_EQUAL(2, -1);
   CU_ASSERT_STRING_EQUAL("string #1", "string #1");
   CU_ASSERT_STRING_NOT_EQUAL("string #1", "string #2");

   CU_ASSERT(CU_FALSE);
   CU_ASSERT_EQUAL(2, 3);
   CU_ASSERT_STRING_NOT_EQUAL("string #1", "string #1");
   CU_ASSERT_STRING_EQUAL("string #1", "string #2");
}

void max_test_1(void) {
  CU_ASSERT_EQUAL( 2, 2);
  CU_ASSERT_EQUAL( 2, 2);
}

void magnitude_of_x6_y3_z2_should_be_7(void) {
  struct accelerometer acc_data[1] = {
    {.t = 10, .x=6., .y=3., .z=2.}
  };
  double mag[1];
  magnitude(acc_data ,mag);
  CU_ASSERT_EQUAL( mag[0] , 7);
}

void initialize_struct_accelerometer(void) {
  struct accelerometer acc_data[1] = {
    {.t = 10, .x=6., .y=3., .z=2.}
  };  
  CU_ASSERT_EQUAL( acc_data[0].t , 10);
  CU_ASSERT_EQUAL( acc_data[0].x , 6);
  CU_ASSERT_EQUAL( acc_data[0].y , 3);
  CU_ASSERT_EQUAL( acc_data[0].z , 2);
}

void spatial_data_is_commutative_for_magnitude(void) {
  struct accelerometer acc_data[2] = {
    {.t = 10, .x=3., .y=6., .z=2.},
    {.t = 10, .x=6., .y=3., .z=2.}
  };
  double mag[2];
  magnitude(acc_data, mag);
  CU_ASSERT_EQUAL( mag[0] , mag[1]);
}

void maganitude_should_be_timeindependent(void) {
  struct accelerometer acc_data[2] = {
    {.t = 3, .x=6., .y=3., .z=2.},
    {.t = 8, .x=6., .y=3., .z=2.}
  };
  double mag[2];
  magnitude(acc_data, mag);
  CU_ASSERT_EQUAL( mag[0] , mag[1]);
}


void length_of_accelerometer_struct(void){
  struct accelerometer acc_data[2] = {
    {.t = 10, .x=6., .y=3., .z=2.},
    {.t = 10, .x=6., .y=3., .z=2.}
  };
  size_t length = sizeof(acc_data)/sizeof(acc_data[0]);
  CU_ASSERT_EQUAL(length , 2);
}


void readcsv_line15_comparison(void) {
  struct accelerometer acc_data[7024];
  char filepath[20];
  strcpy(filepath, "AccData.csv");
  readcsv(filepath, acc_data);
  CU_ASSERT_EQUAL( acc_data[15].t , 141);
  CU_ASSERT_EQUAL( acc_data[15].x , 1031.25);
  CU_ASSERT_EQUAL( acc_data[15].y , 31.25);
  CU_ASSERT_EQUAL( acc_data[15].z , -62.5);
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
   if ( (NULL == CU_add_test(pSuite, "max_test_1", max_test_1)) ||
        (NULL == CU_add_test(pSuite, "magnitude_of_x6_y3_z2_should_be_7", magnitude_of_x6_y3_z2_should_be_7)) ||
        (NULL == CU_add_test(pSuite, "initialize_struct_accelerometer", initialize_struct_accelerometer)) ||
        (NULL == CU_add_test(pSuite, "spatial_data_is_commutative_for_magnitude", spatial_data_is_commutative_for_magnitude)) ||
        (NULL == CU_add_test(pSuite, "maganitude_should_be_timeindependent", maganitude_should_be_timeindependent)) ||
        (NULL == CU_add_test(pSuite, "length_of_accelerometer_struct", length_of_accelerometer_struct)) ||
        (NULL == CU_add_test(pSuite, "readcsv_line15_comparison", readcsv_line15_comparison))
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
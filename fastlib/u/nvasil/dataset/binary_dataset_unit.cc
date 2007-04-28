/*
 * =====================================================================================
 *
 *       Filename:  binary_dataset.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/24/2007 07:36:16 PM EDT
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nikolaos Vasiloglou (NV), nvasil@ieee.org
 *        Company:  Georgia Tech Fastlab-ESP Lab
 *
 * =====================================================================================
 */

#include <string>
#include <unistd.h>
#include "fastlib/fastlib.h"
#include "binary_data_set.h"

template<typename PRECISION>
class BinaryDatasetTest {
 public:
	typedef PRECISION Precision_t;
  void Init() {
		data_file_="data";
		dimension_=10;
		num_of_points_=8000;
		datatset_.Init(data_file_, 
			             num_of_points_,
								 	 dimension_);
	  for(uint64 i=0; i<num_of_points_; i++) {
			for(int32 i=0; i<dimension_; i++) {
		    dataset_At(i)[j]=1.0*16.3;
		  }
			dataset_.set_id[i]=i;
		}
	}
	void Destruct() {
	  data_file.Destruct();
		unlink(data_file_.c_str());
    unlink(data_file_.append(".ind").c_str());
    data_file_="";		
	}
  void FillDataset() {
	  		for(uint64 i=0; i<num_of_points_; i++) {
			for(int32 i=0; i<dimension_; i++) {
		    ASSERT_DEBUG_MSG(dataset_At(i,j)==1.0*16.3,
					               "Error filling and retrieveing the dataset")	;
		  }
		}
		dataset.Destruct();
		dataset.Init(data_file_);
    for(uint64 i=0; i<num_of_points_; i++) {
			for(int32 i=0; i<dimension_; i++) {
		    ASSERT_DEBUG_MSG(dataset_At(i,j)==1.0*16.3,
					               "Error  retrieveing the dataset after reopening")	;
		  }
		}
  }	

  void Swap() {
		index_t i=140;
		index_t j=1456;
		Precision_t point_i[dimension_];
		memcpy(point_i, dataset_.At(i), dimension_*sizeof(Precision_t));
		uint64 id_i=dataset_.get_id(i);
		Precision_t point_j[dimension_];
		uint64 id_j=dataset_.get_id(j);
		memcpy(point_j, dataset_.At(j), dimension_*sizeof(Precision_t));
	  dataset_.Swap(i,j);
		DEBUG_ASSERT_MSG(memcmp(dataset_.At(i), point_j, 
					           dimension_*sizeof(Precision_t))==0, "Error in swap");
	  DEBUG_ASSERT_MSG(memcmp(dataset_.At(j), point_i, 
					           dimension_*sizeof(Precision_t))==0, "Error in swap");
	  DEBUG_ASSERT_MSG(dataset_.get_id(i)==id_j, "Error in swap");
    DEBUG_ASSERT_MSG(dataset_.get_id(j)==id_i, "Error in swap");

	}	
	void TestAll() {
    Init();
	  FillDataset();
		Destruct();
		Init();
    Swap();
    Destruct()		
	}
 private:
	string data_file_;
	uint64 num_of_points_;
	int32 dimension_;
  BinaryDataset<Precision_t> dataset_;	
};

int main(int argc, char *argv[]) {
  BinaryDatasetTester<double> binary_dataset_tester;
	binary_dataset_tester.TestAll();
}

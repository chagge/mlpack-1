/*
 * =====================================================================================
 * 
 *       Filename:  hyper_ball.h
 * 
 *    Description:  
 * 
 *        Version:  1.0
 *        Created:  02/11/2007 05:45:21 PM EST
 *       Revision:  none
 *       Compiler:  gcc
 * 
 *         Author:  Nikolaos Vasiloglou (NV), nvasil@ieee.org
 *        Company:  Georgia Tech Fastlab-ESP Lab
 * 
 * =====================================================================================
 */
#ifndef HYPER_BALL_H_
#define HYPER_BALL_H_
#include <new>
#include <math.h>
#include <string>
#include "loki/Typelist.h"
#include "fastlib/fastlib.h"
#include "computations_counter.h"


template<typename TYPELIST, bool diagnostic>
typename Precision_t, typename METRIC, 
	       Allocator_t, bool diagnostic>
class HyperBall {
 public:
	typedef loki::TypeAt<TYPELIST, 0>::Result Precision_t;
	typedef loki::TypeAt<TYPELIST, 1>::Result Allocator_t;
  typedef loki::TypeAt<TYPELIST, 2>::Result Metric_t;
	typedef Allocator_t::template ArrayPtr<Precision_t> Array_t;
	typedef HyperBall<TYPELIST, diagnostic> HyperBall_t;
  friend class HyperBall<TYPELIST, diagnostic>;	
  HyperBall();
	Init(int32 dimension);
	void Init(Array_t center, Precision_t radious, 
		        Array_t pivot_left, Array_t pivot_right);
  ~HyperBall() {};
  static void *operator new(size_t size);
  static void  operator delete(void *p);
  HyperBall_t &operator=(const HyperBall_t & other);
	void Alias(const HyperBall_t &other);
	void Copy(const HyperBall_t &other, int32 dimension);
  template<typename POINTTYPE> 
  bool IsWithin(POINTTYPE point, int32 dimension, Precision_t range, 
                ComputationsCounter<diagnostic> &comp);
  Precision_t IsWithin(HyperBall_t &hr,
                       int32 dimension, 
                       Precision_t range,
                       ComputationsCounter<diagnostic> &comp);
  template<typename POINTTYPE> 
  bool CrossesBoundaries(POINTTYPE point, int32 dimension, Precision_t range, 
                         ComputationsCounter<diagnostic> &comp);
  template<typename POINTTYPE1, typename POINTTYPE2>
	static Precision_t Distance(POINTTYPE1 point1, POINTTYPE2 point2, int32 dimension);
	static Precision_t Distance(HyperBall_t &hr1,
                            HyperBall_t &hr2,
                            int32 dimension,
                            ComputationsCounter<diagnostic> &comp);
  static Precision_t Distance(HyperBall_t &hr1,
                            HyperBall_t &hr2,
                            Precision_t threshold_distance,
                            int32 dimension,
                            ComputationsCounter<diagnostic> &comp);                            
  template<typename POINTTYPE, typename NODETYPE>                   	
  pair<Allocator_t::template Ptr<NODETYPE>, 
		   Allocator_t::template Ptr<NODETYPE> > 
				 ClosestChild(Allocator_t::template Ptr<NODETYPE> left,
          						Allocator_t::template Ptr<NODETYPE> right,
					             POINTTYPE point, int32 dimension,
											 ComputationsCounter<diagnostic> &comp);                            
  string Print(int32 dimension);

 private:
  Array_t center_;
	// This is the radious, not the square of the radious
	Precision_t radious_;
	Array_t pivot_left_;
	Array_t pivot_right_;
};

#include "hyper_ball_impl.h"
#endif // HYPER_BALL_H_

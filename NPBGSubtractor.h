/*
 *
 * Copyright 2001 by Ahmed Elgammal All  rights reserved.
 *
 * Permission to use, copy,  or modify this software and  its documentation
 * for  educational  and  research purposes only and without fee  is hereby
 * granted, provided  that this copyright notice and the original authors's
 * name appear  on all copies and supporting documentation.  If individual
 * files are  separated from  this  distribution directory  structure, this
 * copyright notice must be included.  For any other uses of this software,
 * in original or  modified form, including but not limited to distribution
 * in whole or in  part, specific  prior permission  must be  obtained from
 * Author or UMIACS.  These programs shall not  be  used, rewritten, or  
 * adapted as  the basis  of  a commercial  software  or  hardware product 
 * without first obtaining appropriate licenses  from Author. 
 * Other than these cases, no part of this software may be used or
 * distributed without written permission of the author.
 *
 * Neither the author nor UMIACS make any representations about the 
 * suitability of this software for any purpose.  It is provided 
 * "as is" without express or implied warranty.
 *
 * Ahmed Elgammal
 * 
 * University of Maryland at College Park
 * UMIACS
 * A.V. Williams Bldg. 
 * CollegePark, MD 20742
 * E-mail:  elgammal@umiacs.umd.edu
 *
 **/


// NPBGSubtractor.h: interface for the NPBGSubtractor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPBGSUBTRACTOR_H__84B0F51E_6E65_41E4_AC01_723B406363C4__INCLUDED_)
#define AFX_NPBGSUBTRACTOR_H__84B0F51E_6E65_41E4_AC01_723B406363C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NPBGmodel.h"
//#include "NCCextract.h"
#include "KernelTable.h"

// kernal look up table settings
#define 	KERNELHALFWIDTH 255
#define 	SEGMAMAX 36.5
#define	  SEGMAMIN 0.5
#define		SEGMABINS 80
#define		DEFAULTSEGMA 1.0

typedef struct{
	unsigned char * Hist;
	unsigned char * MedianBins;
	unsigned char * MedianFreq;
	unsigned char * AccSum;
	unsigned char histbins;
	unsigned char histsum;
	unsigned int  imagesize;
} DynamicMedianHistogram;


typedef struct {
	unsigned int cnt;
	unsigned int * List;
} ImageIndex;


class NPBGSubtractor  
{
private:
	unsigned int rows;
	unsigned int cols;
	unsigned int color_channels;
	unsigned int imagesize;

	//unsigned int SampleSize;

	// flags
	unsigned char UpdateBGFlag;
	unsigned char SdEstimateFlag;
	unsigned char UseColorRatiosFlag;
	unsigned char AdaptBGFlag;
	unsigned char SubsetFlag;
	
	int UpdateSDRate;

	double Threshold;
	double AlphaValue;

	unsigned int TimeIndex;


 	ImageIndex  * imageindex;

						  
	unsigned char * tempFrame;


	KernelLUTable * KernelTable;
						
	NPBGmodel * BGModel;

	DynamicMedianHistogram AbsDiffHist;



	double * Pimage1;
	double * Pimage2;



void NPBGSubtraction_Subset_Kernel(
						unsigned char * image,
						unsigned char * FGImage,
						unsigned char * FilteredFGImage);

void NPBGSubtractor::SequenceBGUpdate_Pairs(unsigned char * image,
						unsigned char * Mask);

public:
	NPBGSubtractor();
	virtual ~NPBGSubtractor();

	int Intialize(unsigned int rows,
								unsigned int cols,
								unsigned int color_channels,
								unsigned int SequenceLength,
								unsigned int TimeWindowSize,
								unsigned char SDEstimationFlag,
								unsigned char UseColorRatiosFlag);

	void AddFrame(unsigned char * ImageBuffer);

	void Estimation();




	void NBBGSubtraction(unsigned char * Frame,
				   unsigned char * FGImage,
				   unsigned char * FilteredFGImage,
				   unsigned char ** DisplayBuffers);



	/*
	void ExtractObjects(unsigned char * FGImage,
		int * ccimage,
		component * CompTable,
		component * GroupTable,
		unsigned int * comp_cnt,
		unsigned int * group_cnt);
	*/

	void Update(unsigned char *);

	void SetThresholds(double th, double alpha) {
		Threshold=th;
		AlphaValue=alpha;
	};


	void SetUpdateFlag(unsigned int bgflag){
		UpdateBGFlag=bgflag;		
	};

};

#endif // !defined(AFX_NPBGSUBTRACTOR_H__84B0F51E_6E65_41E4_AC01_723B406363C4__INCLUDED_)

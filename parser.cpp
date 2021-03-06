/*! \file parser.cpp
 *
 *
 *  \brief <b>This function permits to read the file that contains the data for the matrices
of the Kalman Filter </b>
 *
 *
 *  \author Copyright (C) 2005-2006 by Iacopo Masi <iacopo.masi@gmail.com>
 *   		 	and Nicola Martorana <martorana.nicola@gmail.com>
 *			and Marco Meoni <meonimarco@gmail.com>
 * 			This  code is distributed under the terms of <b>GNU GPL v2</b>
 *
 *  \version $Revision: 0.1 $
 *  \date 2006/10/27 
 * 
 *
 *
 */
 

#include "parser.h"


///The function that parse the data.txt files where are store the Matrix
/**
 * \param filename The name of the file to parse
 * \param ValuesVect The pointer to the vector that will contain the values
 * \param MDSC The pointer to the structure that contains the info for each matrix: numbers of Rows and Cols 
 */

void parse(wxString fileName,float* ValuesVect,struct matrixDesc* MDSC){
 	
	wxString Stringa;
	
	//!It mus be not written,but a filename passed in the char* fileName variable
	wxFFile file(fileName.GetData());
	file.ReadAll(&Stringa);//!put the content of the file in a string

	int nMatrix = Stringa.Freq(']');//!# matrices in data file

		
	int zz=0;
	
	for (int i=0;i<nMatrix;i++){
		wxString Matrix = Stringa.AfterFirst('[');
		Matrix = Matrix.BeforeFirst(']');
		int s = Matrix.size();
		Stringa.Remove(0,s+2);
		
		Matrix += ';';
		int nRows = Matrix.Freq(';');//!# rows of the matrix
		MDSC[i].nRows=nRows;
		for (int j=0;j<nRows;j++){
			wxString Row = Matrix.BeforeFirst(';');
			int z;
			z = Row.size();
			Matrix.Remove(0,z+1);
			
			Row +=(',');
			int nCols = Row.Freq(',');
			MDSC[i].nCols=nCols;//!# cols of the matrix
			
			//!Getting the  data

			for (int h=0;h<nCols;h++){
				wxString Col = Row.BeforeFirst(',');
				
				//const char* col = (const char *) Col.c_str(); // modified to be compiled under linux
				
				double val;
				Col.ToDouble(&val);
				
				ValuesVect[zz]=val;//!put the data in the vector
				zz++;
				int p;
				p = Col.size();
				Row.Remove(0,p+1);


			}
			}
		}
	file.Close();

}

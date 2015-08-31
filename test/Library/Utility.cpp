//
//  Utility.cpp
//  test
//
//  Created by Chukie on 15/9/1.
//  Copyright (c) 2015年 Chukie. All rights reserved.
//

#include "Utility.h"
#include <fstream>

namespace Library
{
    void Utility::LoadBinaryFile(const std::string& filename, std::vector<char>& data)
    {
        std::ifstream file = std::ifstream(filename.c_str(), std::ios::binary);
    
        if (file.bad())
        {
            assert(false);
        }
        
        file.seekg(0, std::ios::end);
        unsigned int size = (unsigned int)file.tellg();
        
        if (size > 0)
        {
            data.resize(size);
            file.seekg(0, std::ios::beg);
            file.read(&data.front(), size);
        }
        
        file.close();
        
//        FILE *fptr;
//        long length;
//        char *buf;
//        
//        fptr = fopen(filename.c_str(), "rb"); /* Open file for reading */
//        assert(fptr);
//        fseek(fptr, 0, SEEK_END); /* Seek to the end of the file */
//        length = ftell(fptr); /* Find out how many bytes into the file we are */
//        buf = (char*)malloc(length+1); /* Allocate a buffer for the entire length of the file and a null terminator */
//        fseek(fptr, 0, SEEK_SET); /* Go back to the beginning of the file */
//        fread(&data.front(), length, 1, fptr); /* Read the contents of the file in to the buffer */
//        fclose(fptr); /* Close the file */
        //buf[length] = 0; /* Null terminator */
        
        //return buf; /* Return the buffer */
    }
};

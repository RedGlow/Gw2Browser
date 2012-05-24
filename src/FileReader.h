/** \file       FileReader.h
 *  \brief      Contains the declaration of the base class of readers for the 
 *              various file types.
 *  \author     Rhoot
 */

/*	Copyright (C) 2012 Rhoot <https://github.com/rhoot>

    This file is part of Gw2Browser.

    Gw2Browser is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#ifndef FILEREADER_H_INCLUDED
#define FILEREADER_H_INCLUDED

#include "Util/Array.h"
#include "ANetStructs.h"

namespace gw2b
{

/** Data used by the FileReader, both for creation and internal storage. */
struct FileReaderData
{
    byte*        mData;         /**< Data to be read. */
    uint         mSize;         /**< Size of the data to be read. */
    ANetFileType mFileType;     /**< File type of the data being read. */
};

/** Base class for all supported file readers. Also handles everything
 *  unsupported by other file readers. */
class FileReader
{
protected:
    FileReaderData  mData;
public:
    /** Type of data contained in this file. Determines how it is exported. */
    enum DataType
    {
        DT_None,            /**< Invalid data. */
        DT_Binary,          /**< Binary data. Usually for unsupported types. */
        DT_Image,           /**< Image data. */
        DT_Sound,           /**< Sound data. */
    };
public:
    /** Constructor.
     *  \param[in]  pData       Data to be handled by this reader. */
    FileReader(const FileReaderData& pData);
    /** Destructor. Clears all data. */
    virtual ~FileReader();

    /** Clears all data contained in this reader. */
    virtual void Clean();
    /** Gets the type of data contained in this file. Not to be confused with
     *  file type.
     *  \return DataType    type of data. */
    virtual DataType GetDataType() const        { return DT_Binary; }
    /** Gets an appropriate file extension for the contents of this reader.
     *  \return wxString    File extension. */
    virtual const wxChar* GetExtension() const  { return wxT("raw"); }
    /** Converts the data associated with this file into a usable format.
     *  The caller is responsible for cleanup the malloc'd data.
     *  \param[out] pOutSize    size of converted data.
     *  \return byte*   converted data. */
    virtual byte* ConvertData(uint& pOutSize) const;

    /** Analyzes the given data and creates an appropriate subclass of 
     *  FileReader to handle it. Caller is responsible for freeing the reader.
     *  \param[in]  pData   Data to read.
     *  \return FileReader* Newly created FileReader for the data. */
    static FileReader* GetReaderForData(const FileReaderData& pData);
};

}; // namespace gw2b

#endif // FILEREADER_H_INCLUDED

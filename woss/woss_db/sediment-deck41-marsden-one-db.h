/* WOSS - World Ocean Simulation System -
 * 
 * Copyright (C) 2009 Federico Guerra
 * and regents of the SIGNET lab, University of Padova
 *
 * Author: Federico Guerra - federico@guerra-tlc.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */ 

/*
 * This software has been developed by Federico Guerra and SIGNET lab,
 * University of Padova, in collaboration with the NATO Centre for 
 * Maritime Research and Experimentation (http://www.cmre.nato.int ; 
 * E-mail: pao@cmre.nato.int), whose support is gratefully acknowledged.
 */


/**
 * @file   sediment-deck41-marsden-one-db.h
 * @author Federico Guerra
 * 
 * \brief Provides the interface for woss::SedimDeck41MarsdenOneDb class
 *
 * Provides the interface for the woss::SedimDeck41MarsdenOneDb class
 */


#ifndef WOSS_SEDIMENT_DECK41_MARSDEN_ONE_DB_H 
#define WOSS_SEDIMENT_DECK41_MARSDEN_ONE_DB_H


#ifdef WOSS_NETCDF_SUPPORT


#include <sediment-definitions.h>
#include "woss-db.h"


namespace woss {
  
    
  /**
  * \brief WossDb for custom made NetCDF marsden coordinates DECK41 Sediment database
  *
  * SedimDeck41MarsdenOneDb implements WossNetcdfDb for the custom made NetCDF marsden coordinates DECK41 Sediment database
  **/
  class SedimDeck41MarsdenOneDb : public WossNetcdfDb {


    public:
      

    /**
    * SedimDeck41MarsdenOneDb default constructor. Default constructed object are not valid
    * @param name pathname of database
    **/
    SedimDeck41MarsdenOneDb( const ::std::string& name = DB_NAME_NOT_SET );

    virtual ~SedimDeck41MarsdenOneDb() { }


    /**
    * Returns a Deck41Types for the given coordinates
    * @param coordinates const reference to a valid MarsdenCoord object
    * @returns a Deck41Types value ( main type value, secondary type value )
    **/
    Deck41Types getSeaFloorType( const MarsdenCoord& marsden_coord ) const; 


    /**
    * Checks the validity of SedimDeck41MarsdenOneDb 
    * @return <i>true</i> if pathname is valid, <i>false</i> otherwise
    **/
    virtual bool isValid() { return( WossNetcdfDb::isValid() && db_name != DB_NAME_NOT_SET ); }


    /**
    * Post openConnection() actions, used to create and initialize NetCDF variables
    * @return <i>true</i> if method was successful, <i>false</i> otherwise
    **/
    virtual bool finalizeConnection();

    
    protected:
      

    /**
    * NetCDF variable representing main DECK41 floortype 
    **/
    NcVar* main_sedim_var_marsden_one;

    /**
    * NetCDF variable representing secondary DECK41 floortype 
    **/
    NcVar* sec_sedim_var_marsden_one;


  };

  
}

#endif // WOSS_NETCDF_SUPPORT

#endif /* WOSS_SEDIMENT_DECK41_MARSDEN_ONE_DB_H */

  
 
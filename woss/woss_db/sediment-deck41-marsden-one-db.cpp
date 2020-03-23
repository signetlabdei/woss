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
 * @file   sediment-deck41-marsden-one-db.cpp
 * @author Federico Guerra
 * 
 * \brief Provides the implementation of woss::SedimDeck41MarsdenOneDb class
 *
 * Provides the implementation of the woss::SedimDeck41MarsdenOneDb class
 */

#ifdef WOSS_NETCDF_SUPPORT

#include <cstdlib>
#include "sediment-deck41-marsden-one-db.h" 


using namespace woss;


SedimDeck41MarsdenOneDb::SedimDeck41MarsdenOneDb( const ::std::string& name ) 
: WossNetcdfDb( name ),
  main_sedim_var_marsden_one(0),
  sec_sedim_var_marsden_one(0)
{
}


bool SedimDeck41MarsdenOneDb::finalizeConnection() {
  main_sedim_var_marsden_one = netcdf_db->get_var("seafloor_main_type");
  sec_sedim_var_marsden_one = netcdf_db->get_var("seafloor_secondary_type");
  return ( (main_sedim_var_marsden_one != 0) && (sec_sedim_var_marsden_one != 0) );
}


Deck41Types SedimDeck41MarsdenOneDb::getSeaFloorType(const MarsdenCoord& marsden_coord) const {
  int main_type;
  int secondary_type;

  if (debug) ::std::cout << "SedimDeck41CoordDb::getSeaFloorType() marsden square " << marsden_coord.first 
                         << "; marsden 10 degrees " << marsden_coord.second << ::std::endl;

  NcBool ret_val = main_sedim_var_marsden_one->set_cur(marsden_coord.first, marsden_coord.second);
  if (!ret_val) {
    ::std::cout << "SedimDeck41MarsdenOneDb::getSeaFloorType() Couldn't set_cur() of main_sedim_var_marsden_one;"
	      << " current indexes = " << marsden_coord.first << " , " << marsden_coord.second << ::std::endl;
    exit(1);
  }
  
  ret_val = sec_sedim_var_marsden_one->set_cur(marsden_coord.first, marsden_coord.second); 
  if (!ret_val) {
    ::std::cout << "SedimDeck41MarsdenOneDb::getSeaFloorType() Couldn't set_cur() of sec_sedim_var_marsden_one;"
	      << " current indexes = " << marsden_coord.first << " , " << marsden_coord.second << ::std::endl;
    exit(1);
  }

  ret_val = main_sedim_var_marsden_one->get(&main_type,1,1);
  if (!ret_val) {
    ::std::cout << "SedimDeck41MarsdenOneDb::getSeaFloorType() Couldn't extract main type; " 
	      << " current indexes = " << marsden_coord.first << " , " << marsden_coord.second << ::std::endl;
    exit(1);
  }
  
  ret_val = sec_sedim_var_marsden_one->get(&secondary_type,1,1);
  if (!ret_val) {
    ::std::cout << "SedimDeck41MarsdenOneDb::getSeaFloorType() Couldn't extract secondary type; "
	      << " current indexes = " << marsden_coord.first << " , " << marsden_coord.second << ::std::endl;
    exit(1);
  }

  if (debug) ::std::cout << "SedimDeck41MarsdenOneDb::getSeaFloorType() mardsen_square = " << marsden_coord.first 
			<< "; mardsen_one_degree = " << marsden_coord.second << "; main type = " 
			<< main_type << "; secondary type = " << secondary_type << ::std::endl;

  return(::std::make_pair(main_type, secondary_type));
}

#endif // WOSS_NETCDF_SUPPORT

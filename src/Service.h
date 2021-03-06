// ----------------------------------------------------------------------------
///  \file   Service.h
///  \brief  Class that provides access to the current event object.
///
///  \author   <paola.ferrario@ific.uv.es>
///  \date     14 Feb 2013
///  \version  $Id: Service.h 9240 2013-09-11 13:02:35Z paola $
///
///  Copyright (c) 2013 NEXT Collaboration
// ----------------------------------------------------------------------------

#ifndef ISERVICE_H_
#define ISERVICE_H_

#include "Event.h"
#include "RootWriter.h"

#include <TVectorD.h>

namespace irene {

  /// This class is a singleton, and provides access to the current event object
  /// and to the class that writes the ROOT file
  class Service {

  private:
    /// Constructor
    Service();
    /// Destructor
    ~Service();

  private:
    static Service* _s_instance; ///< unique instance of the class
    Event* _event; ///< event to be accessed
    RootWriter _root_writer; ///< instance of the class that writes the ROOT file
    TVectorD _mdata; ///< TList of data to be stored
    
  public:
    static Service* GetInstance();
    Event* GetEvent();
    TVectorD& GetDataList();
    RootWriter& GetRootWriter();

  };

  // INLINE methods
  inline Event* Service::GetEvent() {return _event;}
  inline TVectorD& Service::GetDataList() {return _mdata;}
  inline RootWriter& Service::GetRootWriter() {return _root_writer;}
	  
} // end namespace irene

#endif

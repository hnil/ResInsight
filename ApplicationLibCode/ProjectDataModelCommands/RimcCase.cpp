/////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2026- Equinor ASA
//
//  ResInsight is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  ResInsight is distributed in the hope that it will be useful, but WITHOUT ANY
//  WARRANTY; without even the implied warranty of MERCHANTABILITY or
//  FITNESS FOR A PARTICULAR PURPOSE.
//
//  See the GNU General Public License at <http://www.gnu.org/licenses/gpl.html>
//  for more details.
//
/////////////////////////////////////////////////////////////////////////////////

#include "RimcCase.h"

#include "RicCloseCaseFeature.h"

#include "RimCase.h"

CAF_PDM_OBJECT_METHOD_SOURCE_INIT( RimCase, RimcCase_close, "close" );

//--------------------------------------------------------------------------------------------------
///
//--------------------------------------------------------------------------------------------------
RimcCase_close::RimcCase_close( caf::PdmObjectHandle* self )
    : caf::PdmVoidObjectMethod( self )
{
    CAF_PDM_InitObject( "Close Case", "", "", "Close the case and its views" );
}

//--------------------------------------------------------------------------------------------------
///
//--------------------------------------------------------------------------------------------------
std::expected<caf::PdmObjectHandle*, QString> RimcCase_close::execute()
{
    auto rimCase = self<RimCase>();
    if ( !rimCase ) return std::unexpected( "Unable to get case." );

    RicCloseCaseFeature::closeCase( rimCase );
    return nullptr;
}

/////////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2026 Equinor ASA
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

#include "RimFilterDisplayUtil.h"

#include "RimCellFilter.h"

#include <QStringList>

QString RimFilterDisplayUtil::filterNamesJoined( const std::vector<RimCellFilter*>& filters, bool useAndOperation )
{
    // Include filters of one kind add up; the combine mode applies only between index and other filters.
    QStringList indexNames, otherNames, excludeNames;
    for ( auto* f : filters )
    {
        if ( !f || !f->isFilterEnabled() ) continue;
        if ( f->filterMode() == RimCellFilter::EXCLUDE )
            excludeNames << f->name();
        else if ( f->isIndexFilter() )
            indexNames << f->name();
        else
            otherNames << f->name();
    }

    auto group = []( const QStringList& names, bool parenthesize )
    {
        const QString joined = names.join( QStringLiteral( " OR " ) );
        return ( parenthesize && names.size() > 1 ) ? QStringLiteral( "(%1)" ).arg( joined ) : joined;
    };

    QStringList parts;
    const bool  both = !indexNames.isEmpty() && !otherNames.isEmpty();
    if ( !otherNames.isEmpty() ) parts << group( otherNames, both );
    if ( !indexNames.isEmpty() ) parts << group( indexNames, both );

    QString text = parts.join( useAndOperation ? QStringLiteral( " AND " ) : QStringLiteral( " OR " ) );
    for ( const auto& name : excludeNames )
    {
        text += text.isEmpty() ? QStringLiteral( "NOT %1" ).arg( name ) : QStringLiteral( " AND NOT %1" ).arg( name );
    }
    return text;
}

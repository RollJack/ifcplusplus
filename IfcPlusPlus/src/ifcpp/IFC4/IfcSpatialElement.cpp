/* -*-c++-*- IfcPlusPlus - www.ifcplusplus.com - Copyright (C) 2011 Fabian Gerold
*
* This library is open source and may be redistributed and/or modified under  
* the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
* (at your option) any later version.  The full license is in LICENSE file
* included with this distribution, and on the openscenegraph.org website.
* 
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
* OpenSceneGraph Public License for more details.
*/
#include <sstream>
#include <limits>

#include "ifcpp/model/IfcPPException.h"
#include "ifcpp/model/IfcPPAttributeObject.h"
#include "ifcpp/model/IfcPPGuid.h"
#include "ifcpp/reader/ReaderUtil.h"
#include "ifcpp/writer/WriterUtil.h"
#include "ifcpp/IfcPPEntityEnums.h"
#include "include/IfcGloballyUniqueId.h"
#include "include/IfcLabel.h"
#include "include/IfcObjectPlacement.h"
#include "include/IfcOwnerHistory.h"
#include "include/IfcProductRepresentation.h"
#include "include/IfcRelAggregates.h"
#include "include/IfcRelAssigns.h"
#include "include/IfcRelAssignsToProduct.h"
#include "include/IfcRelAssociates.h"
#include "include/IfcRelContainedInSpatialStructure.h"
#include "include/IfcRelDeclares.h"
#include "include/IfcRelDefinesByObject.h"
#include "include/IfcRelDefinesByProperties.h"
#include "include/IfcRelDefinesByType.h"
#include "include/IfcRelNests.h"
#include "include/IfcRelReferencedInSpatialStructure.h"
#include "include/IfcRelServicesBuildings.h"
#include "include/IfcSpatialElement.h"
#include "include/IfcText.h"

// ENTITY IfcSpatialElement 
IfcSpatialElement::IfcSpatialElement() { m_entity_enum = IFCSPATIALELEMENT; }
IfcSpatialElement::IfcSpatialElement( int id ) { m_id = id; m_entity_enum = IFCSPATIALELEMENT; }
IfcSpatialElement::~IfcSpatialElement() {}
shared_ptr<IfcPPObject> IfcSpatialElement::getDeepCopy( IfcPPCopyOptions& options )
{
	shared_ptr<IfcSpatialElement> copy_self( new IfcSpatialElement() );
	if( m_GlobalId )
	{
		if( options.create_new_IfcGloballyUniqueId ) { copy_self->m_GlobalId = shared_ptr<IfcGloballyUniqueId>(new IfcGloballyUniqueId( CreateCompressedGuidString22() ) ); }
		else { copy_self->m_GlobalId = dynamic_pointer_cast<IfcGloballyUniqueId>( m_GlobalId->getDeepCopy(options) ); }
	}
	if( m_OwnerHistory )
	{
		if( options.shallow_copy_IfcOwnerHistory ) { copy_self->m_OwnerHistory = m_OwnerHistory; }
		else { copy_self->m_OwnerHistory = dynamic_pointer_cast<IfcOwnerHistory>( m_OwnerHistory->getDeepCopy(options) ); }
	}
	if( m_Name ) { copy_self->m_Name = dynamic_pointer_cast<IfcLabel>( m_Name->getDeepCopy(options) ); }
	if( m_Description ) { copy_self->m_Description = dynamic_pointer_cast<IfcText>( m_Description->getDeepCopy(options) ); }
	if( m_ObjectType ) { copy_self->m_ObjectType = dynamic_pointer_cast<IfcLabel>( m_ObjectType->getDeepCopy(options) ); }
	if( m_ObjectPlacement ) { copy_self->m_ObjectPlacement = dynamic_pointer_cast<IfcObjectPlacement>( m_ObjectPlacement->getDeepCopy(options) ); }
	if( m_Representation ) { copy_self->m_Representation = dynamic_pointer_cast<IfcProductRepresentation>( m_Representation->getDeepCopy(options) ); }
	if( m_LongName ) { copy_self->m_LongName = dynamic_pointer_cast<IfcLabel>( m_LongName->getDeepCopy(options) ); }
	return copy_self;
}
void IfcSpatialElement::getStepLine( std::stringstream& stream ) const
{
	stream << "#" << m_id << "= IFCSPATIALELEMENT" << "(";
	if( m_GlobalId ) { m_GlobalId->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_OwnerHistory ) { stream << "#" << m_OwnerHistory->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_Name ) { m_Name->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_Description ) { m_Description->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_ObjectType ) { m_ObjectType->getStepParameter( stream ); } else { stream << "*"; }
	stream << ",";
	if( m_ObjectPlacement ) { stream << "#" << m_ObjectPlacement->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_Representation ) { stream << "#" << m_Representation->m_id; } else { stream << "*"; }
	stream << ",";
	if( m_LongName ) { m_LongName->getStepParameter( stream ); } else { stream << "$"; }
	stream << ");";
}
void IfcSpatialElement::getStepParameter( std::stringstream& stream, bool ) const { stream << "#" << m_id; }
void IfcSpatialElement::readStepArguments( const std::vector<std::wstring>& args, const boost::unordered_map<int,shared_ptr<IfcPPEntity> >& map )
{
	const int num_args = (int)args.size();
	if( num_args != 8 ){ std::stringstream err; err << "Wrong parameter count for entity IfcSpatialElement, expecting 8, having " << num_args << ". Entity ID: " << m_id << std::endl; throw IfcPPException( err.str().c_str() ); }
	m_GlobalId = IfcGloballyUniqueId::createObjectFromSTEP( args[0] );
	readEntityReference( args[1], m_OwnerHistory, map );
	m_Name = IfcLabel::createObjectFromSTEP( args[2] );
	m_Description = IfcText::createObjectFromSTEP( args[3] );
	m_ObjectType = IfcLabel::createObjectFromSTEP( args[4] );
	readEntityReference( args[5], m_ObjectPlacement, map );
	readEntityReference( args[6], m_Representation, map );
	m_LongName = IfcLabel::createObjectFromSTEP( args[7] );
}
void IfcSpatialElement::getAttributes( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes )
{
	IfcProduct::getAttributes( vec_attributes );
	vec_attributes.push_back( std::make_pair( "LongName", m_LongName ) );
}
void IfcSpatialElement::getAttributesInverse( std::vector<std::pair<std::string, shared_ptr<IfcPPObject> > >& vec_attributes_inverse )
{
	IfcProduct::getAttributesInverse( vec_attributes_inverse );
	if( m_ContainsElements_inverse.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> ContainsElements_inverse_vec_obj( new IfcPPAttributeObjectVector() );
		for( size_t i=0; i<m_ContainsElements_inverse.size(); ++i )
		{
			if( !m_ContainsElements_inverse[i].expired() )
			{
				ContainsElements_inverse_vec_obj->m_vec.push_back( shared_ptr<IfcRelContainedInSpatialStructure>( m_ContainsElements_inverse[i] ) );
			}
		}
		vec_attributes_inverse.push_back( std::make_pair( "ContainsElements_inverse", ContainsElements_inverse_vec_obj ) );
	}
	if( m_ServicedBySystems_inverse.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> ServicedBySystems_inverse_vec_obj( new IfcPPAttributeObjectVector() );
		for( size_t i=0; i<m_ServicedBySystems_inverse.size(); ++i )
		{
			if( !m_ServicedBySystems_inverse[i].expired() )
			{
				ServicedBySystems_inverse_vec_obj->m_vec.push_back( shared_ptr<IfcRelServicesBuildings>( m_ServicedBySystems_inverse[i] ) );
			}
		}
		vec_attributes_inverse.push_back( std::make_pair( "ServicedBySystems_inverse", ServicedBySystems_inverse_vec_obj ) );
	}
	if( m_ReferencesElements_inverse.size() > 0 )
	{
		shared_ptr<IfcPPAttributeObjectVector> ReferencesElements_inverse_vec_obj( new IfcPPAttributeObjectVector() );
		for( size_t i=0; i<m_ReferencesElements_inverse.size(); ++i )
		{
			if( !m_ReferencesElements_inverse[i].expired() )
			{
				ReferencesElements_inverse_vec_obj->m_vec.push_back( shared_ptr<IfcRelReferencedInSpatialStructure>( m_ReferencesElements_inverse[i] ) );
			}
		}
		vec_attributes_inverse.push_back( std::make_pair( "ReferencesElements_inverse", ReferencesElements_inverse_vec_obj ) );
	}
}
void IfcSpatialElement::setInverseCounterparts( shared_ptr<IfcPPEntity> ptr_self_entity )
{
	IfcProduct::setInverseCounterparts( ptr_self_entity );
}
void IfcSpatialElement::unlinkFromInverseCounterparts()
{
	IfcProduct::unlinkFromInverseCounterparts();
}

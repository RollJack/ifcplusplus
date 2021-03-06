#pragma once

#pragma warning (disable: 4267 4334 4244 4100)
#include <vector>
#include <carve/carve.hpp>
#include <carve/matrix.hpp>
#include <carve/geom2d.hpp>
#include <carve/geom3d.hpp>
#include <common/geometry.hpp>
#include <carve/poly.hpp>
#include <carve/polyhedron_base.hpp>
#include <carve/mesh.hpp>
#include <carve/mesh_simplify.hpp>
#include <carve/input.hpp>

#ifndef CARVE_CSG_TRIANGULATOR_INCLUDE
	#define CARVE_CSG_TRIANGULATOR_INCLUDE
	#include <carve/csg_triangulator.hpp>
#endif

namespace carve{
	namespace geom2d{
		int lineSegmentPolyIntersections( const std::vector<carve::geom::vector<2> >& points, carve::geom2d::LineSegment2 line, std::vector<carve::geom2d::PolyIntersectionInfo> &out );
	}
}

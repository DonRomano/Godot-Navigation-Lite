#ifndef NAVIGATION_MESH_H
#define NAVIGATION_MESH_H

#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <Godot.hpp>
#include <Spatial.hpp>
#include <Geometry.hpp>
#include <Node.hpp>
#include <Ref.hpp>
#include <SpatialMaterial.hpp>
#include <SceneTree.hpp>
#include <MeshInstance.hpp>
#include <Mesh.hpp>
#include <ArrayMesh.hpp>

#include "helpers.h"
#include "navmesh_parameters.h"
#include "tilecache_helpers.h"
#include "DetourNavMesh.h"
#include "DetourNavMeshBuilder.h"
#include "DetourTileCache.h"
#include "Recast.h"
#include "filemanager.h"


namespace godot {
	struct NavMeshProcess;
	class DetourNavigationMesh : public Spatial {
		GODOT_CLASS(DetourNavigationMesh, Spatial);
	protected:
		std::vector<Ref<Mesh>> *input_meshes;
		std::vector<Transform> *input_transforms;
		std::vector<AABB> *input_aabbs;
	public:
		DetourNavigationMesh();
		~DetourNavigationMesh();

		void _init();
		void _ready();
		void build_navmesh();
		static void _register_methods();

		bool alloc();
		void release_navmesh();
		bool unsigned_int();

		dtNavMesh* load_mesh();
		void save_mesh();

		void build_debug_mesh();
		void find_path();
		Ref<Material> get_debug_navigation_material();
		virtual dtTileCache* get_tile_cache() { return nullptr; };
		MeshInstance* debug_mesh_instance = nullptr;

		AABB bounding_box;
		dtNavMesh* detour_navmesh = nullptr;
		Ref<ArrayMesh> debug_mesh;
		Transform global_transform;
		Ref<NavmeshParameters> navmesh_parameters;

		void init_mesh_data(
			std::vector<Ref<Mesh>> *meshes, std::vector<Transform> *transforms,
			std::vector<AABB> *aabbs, Transform g_transform
		) {
			global_transform = g_transform;
			input_aabbs = aabbs;
			input_transforms = transforms;
			input_meshes = meshes;
		}

		dtNavMesh* get_detour_navmesh() {
			return detour_navmesh;
		}

		void init_navigation_mesh_values();

		void clear_debug_mesh() {
			if (debug_mesh.is_valid()) {
				debug_mesh.unref();
				Godot::print("Cleared debug mesh.");
			}
		}

		Ref<ArrayMesh> get_debug_mesh();
	};

}
#endif
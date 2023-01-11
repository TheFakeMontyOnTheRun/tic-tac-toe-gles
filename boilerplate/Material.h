//
// Created by monty on 24/09/16.
//

#ifndef DUNGEONSOFNOUDAR_NDK_MATERIAL_H
#define DUNGEONSOFNOUDAR_NDK_MATERIAL_H

namespace odb {
	class Material {
	public:
		std::shared_ptr<NativeBitmap> mBitmap{};

		std::string diffuseMapFilename{};
		std::string normalMapFilename{};
	};
}

#endif //DUNGEONSOFNOUDAR_NDK_MATERIAL_H

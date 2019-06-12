// Copyright (C) 2017 Jérôme Leclercq
// This file is part of the "Nazara Engine - Graphics module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Graphics/SlicedSprite.hpp>
#include <Nazara/Graphics/AbstractRenderQueue.hpp>
#include <Nazara/Utility/VertexStruct.hpp>
#include <Nazara/Graphics/Debug.hpp>

namespace Nz
{

	void SlicedSprite::AddToRenderQueue(AbstractRenderQueue* renderQueue, const InstanceData& instanceData, const Recti& scissorRect) const
	{
		if (m_nbQuads > 0)
		{
			const VertexStruct_XYZ_Color_UV* vertices = reinterpret_cast<const VertexStruct_XYZ_Color_UV*>(instanceData.data.data());
			renderQueue->AddSprites(instanceData.renderOrder, GetMaterial(), vertices, m_nbQuads, scissorRect);
		}
	}

	std::unique_ptr<InstancedRenderable> SlicedSprite::Clone() const
	{
		return std::make_unique<SlicedSprite>(*this);
	}

	void SlicedSprite::MakeBoundingVolume() const
	{
		Vector3f origin(m_origin.x, -m_origin.y, m_origin.z);

		m_boundingVolume.Set(-origin, m_size.x*Vector3f::Right() + m_size.y*Vector3f::Down() - origin);
	}

	bool SlicedSprite::SetMaterial(String materialName, bool resizeSprite)
	{
		MaterialRef material = MaterialLibrary::Query(materialName);
		if (!material)
		{
			material = MaterialManager::Get(materialName);
			if (!material)
			{
				NazaraError("Failed to get material \"" + materialName + "\"");
				return false;
			}
		}

		SetMaterial(std::move(material), resizeSprite);
		return true;
	}

	bool SlicedSprite::SetMaterial(std::size_t skinIndex, String materialName, bool resizeSprite)
	{
		MaterialRef material = MaterialLibrary::Query(materialName);
		if (!material)
		{
			material = MaterialManager::Get(materialName);
			if (!material)
			{
				NazaraError("Failed to get material \"" + materialName + "\"");
				return false;
			}
		}

		SetMaterial(skinIndex, std::move(material), resizeSprite);
		return true;
	}

	bool SlicedSprite::SetTexture(String textureName, bool resizeSprite)
	{
		TextureRef texture = TextureLibrary::Query(textureName);
		if (!texture)
		{
			texture = TextureManager::Get(textureName);
			if (!texture)
			{
				NazaraError("Failed to get texture \"" + textureName + "\"");
				return false;
			}
		}

		SetTexture(std::move(texture), resizeSprite);
		return true;
	}

	bool SlicedSprite::SetTexture(std::size_t skinIndex, String textureName, bool resizeSprite)
	{
		TextureRef texture = TextureLibrary::Query(textureName);
		if (!texture)
		{
			texture = TextureManager::Get(textureName);
			if (!texture)
			{
				NazaraError("Failed to get texture \"" + textureName + "\"");
				return false;
			}
		}

		SetTexture(skinIndex, std::move(texture), resizeSprite);
		return true;
	}

	void SlicedSprite::UpdateData(InstanceData* instanceData) const
	{
		UpdateNbRenderedQuads();

		instanceData->data.resize(4 * m_nbQuads * sizeof(VertexStruct_XYZ_Color_UV));
		VertexStruct_XYZ_Color_UV* vertices = reinterpret_cast<VertexStruct_XYZ_Color_UV*>(instanceData->data.data());

		SparsePtr<Color> colorPtr(&vertices[0].color, sizeof(VertexStruct_XYZ_Color_UV));
		SparsePtr<Vector3f> posPtr(&vertices[0].position, sizeof(VertexStruct_XYZ_Color_UV));
		SparsePtr<Vector2f> texCoordPtr(&vertices[0].uv, sizeof(VertexStruct_XYZ_Color_UV));

		const MaterialRef& material = GetMaterial();
		NazaraAssert(material->HasDiffuseMap(), "Sprite material has no diffuse map");

		Texture* diffuseMap = material->GetDiffuseMap();

		auto width = diffuseMap->GetWidth();
		auto height = diffuseMap->GetHeight();

		float topSize = m_topMargin * height;
		float downSize = m_downMargin * height;
		float leftSize = m_leftMargin * width;
		float rightSize = m_rightMargin * width;

		Vector3f origin(m_origin.x, -m_origin.y, m_origin.z);

		for(unsigned int i = 0 ; i < 4 * m_nbQuads ; i++)
			*colorPtr++ = m_color;

		Nz::Vector2f topLeft = m_textureCoords.GetCorner(RectCorner_LeftTop);
		Nz::Vector2f downLeft = m_textureCoords.GetCorner(RectCorner_LeftBottom);
		Nz::Vector2f downRight = m_textureCoords.GetCorner(RectCorner_RightBottom);
		Nz::Vector2f topRight = m_textureCoords.GetCorner(RectCorner_RightTop);

		if (m_topMargin > 0 && m_leftMargin > 0)
		{
			*posPtr++ = instanceData->transformMatrix.Transform(-origin);
			*texCoordPtr++ = topLeft;

			*posPtr++ = instanceData->transformMatrix.Transform(leftSize * Vector3f::Right() - origin);
			*texCoordPtr++ = topLeft + Vector2f(m_leftMargin, 0);

			*posPtr++ = instanceData->transformMatrix.Transform(topSize * Vector3f::Down() - origin);
			*texCoordPtr++ = topLeft + Vector2f(0, m_topMargin);

			*posPtr++ = instanceData->transformMatrix.Transform(leftSize * Vector3f::Right() + topSize * Vector3f::Down() - origin);
			*texCoordPtr++ = topLeft + Vector2f(m_leftMargin, m_topMargin);
		}
		if (m_leftMargin > 0 && topSize + downSize < m_size.y)
		{
			*posPtr++ = instanceData->transformMatrix.Transform(topSize * Vector3f::Down() - origin);
			*texCoordPtr++ = topLeft + Vector2f(0, m_topMargin);

			*posPtr++ = instanceData->transformMatrix.Transform(leftSize * Vector3f::Right() + topSize * Vector3f::Down() - origin);
			*texCoordPtr++ = topLeft + Vector2f(m_leftMargin, m_topMargin);

			*posPtr++ = instanceData->transformMatrix.Transform((m_size.y - downSize) * Vector3f::Down() - origin);
			*texCoordPtr++ = downLeft + Vector2f(0, -m_downMargin);

			*posPtr++ = instanceData->transformMatrix.Transform(leftSize * Vector3f::Right() + (m_size.y - downSize) * Vector3f::Down() - origin);
			*texCoordPtr++ = downLeft + Vector2f(m_leftMargin, -m_downMargin);

		}
		if (m_leftMargin > 0 && m_downMargin > 0)
		{
			*posPtr++ = instanceData->transformMatrix.Transform((m_size.y - downSize) * Vector3f::Down() - origin);
			*texCoordPtr++ = *texCoordPtr++ = downLeft + Vector2f(0, -m_downMargin);

			*posPtr++ = instanceData->transformMatrix.Transform(leftSize * Vector3f::Right() + (m_size.y - downSize) * Vector3f::Down() - origin);
			*texCoordPtr++ = downLeft + Vector2f(m_leftMargin, -m_downMargin);

			*posPtr++ = instanceData->transformMatrix.Transform(m_size.y * Vector3f::Down() - origin);
			*texCoordPtr++ = downLeft;

			*posPtr++ = instanceData->transformMatrix.Transform(leftSize * Vector3f::Right() + m_size.y * Vector3f::Down() - origin);
			*texCoordPtr++ = downLeft + Vector2f(m_leftMargin, 0);
		}
		if (m_downMargin > 0 && leftSize + rightSize < m_size.x)
		{
			*posPtr++ = instanceData->transformMatrix.Transform(leftSize * Vector3f::Right() + (m_size.y - downSize) * Vector3f::Down() - origin);
			*texCoordPtr++ = downLeft + Vector2f(m_leftMargin, -m_downMargin);

			*posPtr++ = instanceData->transformMatrix.Transform((m_size.x - rightSize) * Vector3f::Right() + (m_size.y - downSize) * Vector3f::Down() - origin);
			*texCoordPtr++ = downRight + Vector2f(-m_rightMargin, -m_downMargin);

			*posPtr++ = instanceData->transformMatrix.Transform(leftSize * Vector3f::Right() + m_size.y * Vector3f::Down() - origin);
			*texCoordPtr++ = downLeft + Vector2f(m_leftMargin, 0);

			*posPtr++ = instanceData->transformMatrix.Transform((m_size.x - rightSize) * Vector3f::Right() + m_size.y * Vector3f::Down() - origin);
			*texCoordPtr++ = downRight + Vector2f(-m_rightMargin, 0);
		}
		if (m_downMargin > 0 && m_rightMargin > 0)
		{
			*posPtr++ = instanceData->transformMatrix.Transform((m_size.x - rightSize) * Vector3f::Right() + (m_size.y - downSize) * Vector3f::Down() - origin);
			*texCoordPtr++ = downRight + Vector2f(-m_rightMargin, -m_downMargin);

			*posPtr++ = instanceData->transformMatrix.Transform(m_size.x * Vector3f::Right() + (m_size.y - downSize) * Vector3f::Down() - origin);
			*texCoordPtr++ = downRight + Vector2f(0, -m_downMargin);

			*posPtr++ = instanceData->transformMatrix.Transform((m_size.x - rightSize) * Vector3f::Right() + m_size.y * Vector3f::Down() - origin);
			*texCoordPtr++ = downRight + Vector2f(-m_rightMargin, 0);

			*posPtr++ = instanceData->transformMatrix.Transform(m_size.x  * Vector3f::Right() + m_size.y * Vector3f::Down() - origin);
			*texCoordPtr++ = downRight;
		}
		if (m_rightMargin > 0 && topSize + downSize < m_size.y)
		{
			*posPtr++ = instanceData->transformMatrix.Transform((m_size.x - rightSize) * Vector3f::Right() + topSize * Vector3f::Down() - origin);
			*texCoordPtr++ = topRight + Vector2f(-m_rightMargin, m_topMargin);

			*posPtr++ = instanceData->transformMatrix.Transform(m_size.x * Vector3f::Right() + topSize * Vector3f::Down() - origin);
			*texCoordPtr++ = topRight + Vector2f(0, m_topMargin);

			*posPtr++ = instanceData->transformMatrix.Transform((m_size.x - rightSize) * Vector3f::Right() + (m_size.y - downSize) * Vector3f::Down() - origin);
			*texCoordPtr++ = downRight + Vector2f(-m_rightMargin, m_downMargin);

			*posPtr++ = instanceData->transformMatrix.Transform(m_size.x * Vector3f::Right() + (m_size.y - downSize) * Vector3f::Down() - origin);
			*texCoordPtr++ = downRight + Vector2f(0, m_downMargin);
		}
		if (m_rightMargin > 0 && m_topMargin > 0)
		{
			*posPtr++ = instanceData->transformMatrix.Transform((m_size.x - rightSize) * Vector3f::Right() - origin);
			*texCoordPtr++ = topRight + Vector2f(-m_rightMargin, 0);

			*posPtr++ = instanceData->transformMatrix.Transform(m_size.x * Vector3f::Right() - origin);
			*texCoordPtr++ = topRight;

			*posPtr++ = instanceData->transformMatrix.Transform((m_size.x - rightSize) * Vector3f::Right() + topSize * Vector3f::Down() - origin);
			*texCoordPtr++ = topRight + Vector2f(-m_rightMargin, m_topMargin);

			*posPtr++ = instanceData->transformMatrix.Transform(m_size.x * Vector3f::Right() + topSize * Vector3f::Down() - origin);
			*texCoordPtr++ = topRight + Vector2f(0, m_topMargin);
		}
		if (m_topMargin > 0 && leftSize + rightSize < m_size.x)
		{
			*posPtr++ = instanceData->transformMatrix.Transform(leftSize * Vector3f::Right() - origin);
			*texCoordPtr++ = topLeft + Vector2f(m_leftMargin, 0);

			*posPtr++ = instanceData->transformMatrix.Transform((m_size.x - rightSize) * Vector3f::Right() - origin);
			*texCoordPtr++ = topRight + Vector2f(-m_rightMargin, 0);

			*posPtr++ = instanceData->transformMatrix.Transform(leftSize * Vector3f::Right() + topSize * Vector3f::Down() - origin);
			*texCoordPtr++ = topLeft + Vector2f(m_leftMargin, m_topMargin);

			*posPtr++ = instanceData->transformMatrix.Transform((m_size.x - rightSize) * Vector3f::Right() + topSize * Vector3f::Down() - origin);
			*texCoordPtr++ = topRight + Vector2f(-m_rightMargin, m_topMargin);
		}

		if (leftSize + rightSize < m_size.x && m_rightMargin > 0 && topSize + downSize < m_size.y)
		{
			*posPtr++ = instanceData->transformMatrix.Transform(leftSize * Vector3f::Right() + topSize * Vector3f::Down() - origin);
			*texCoordPtr++ = topLeft + Vector2f(m_leftMargin, m_topMargin);

			*posPtr++ = instanceData->transformMatrix.Transform((m_size.x - rightSize) * Vector3f::Right() + topSize * Vector3f::Down() - origin);
			*texCoordPtr++ = topRight + Vector2f(-m_rightMargin, m_topMargin);

			*posPtr++ = instanceData->transformMatrix.Transform(leftSize * Vector3f::Right() + (m_size.y - downSize) * Vector3f::Down() - origin);
			*texCoordPtr++ = downLeft + Vector2f(m_leftMargin, -m_downMargin);

			*posPtr++ = instanceData->transformMatrix.Transform((m_size.x - rightSize) * Vector3f::Right() + (m_size.y - downSize) * Vector3f::Down() - origin);
			*texCoordPtr++ = downRight + Vector2f(-m_rightMargin, -m_downMargin);
		}
	}

	void SlicedSprite::UpdateNbRenderedQuads() const
	{
		const MaterialRef& material = GetMaterial();
		NazaraAssert(material->HasDiffuseMap(), "Sprite material has no diffuse map");

		Texture* diffuseMap = material->GetDiffuseMap();

		float width = static_cast<float>(m_size.x) / diffuseMap->GetWidth();
		float height = static_cast<float>(m_size.y) / diffuseMap->GetHeight();

		m_nbQuads = 0;

		if (m_topMargin > 0 && m_leftMargin > 0)
			m_nbQuads++;
		if (m_leftMargin > 0 && m_topMargin + m_downMargin < height)
			m_nbQuads++;
		if (m_leftMargin > 0 && m_downMargin > 0)
			m_nbQuads++;
		if (m_downMargin > 0 && m_leftMargin + m_rightMargin < width)
			m_nbQuads++;
		if (m_downMargin > 0 && m_rightMargin > 0)
			m_nbQuads++;
		if (m_rightMargin > 0 && m_topMargin + m_downMargin < height)
			m_nbQuads++;
		if (m_rightMargin > 0 && m_topMargin > 0)
			m_nbQuads++;
		if (m_topMargin > 0 && m_leftMargin + m_rightMargin < width)
			m_nbQuads++;

		if (m_leftMargin + m_rightMargin < width && m_topMargin + m_downMargin < height)
			m_nbQuads++;
	}

	bool SlicedSprite::Initialize()
	{
		if (!SlicedSpriteLibrary::Initialize())
		{
			NazaraError("Failed to initialise library");
			return false;
		}

		return true;
	}

	void SlicedSprite::Uninitialize()
	{
		SlicedSpriteLibrary::Uninitialize();
	}

	SlicedSpriteLibrary::LibraryMap SlicedSprite::s_library;
}

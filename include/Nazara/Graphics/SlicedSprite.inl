// Copyright (C) 2017 Jérôme Leclercq
// This file is part of the "Nazara Engine - Graphics module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Graphics/SlicedSprite.hpp>
#include <Nazara/Core/Error.hpp>
#include <memory>
#include <Nazara/Graphics/Debug.hpp>

namespace Nz
{
	inline SlicedSprite::SlicedSprite() :
		m_color(Color::White),
		m_textureCoords(0.f, 0.f, 1.f, 1.f),
		m_topMargin(0),
		m_downMargin(0),
		m_leftMargin(0),
		m_rightMargin(0),
		m_size(64.f, 64.f),
		m_origin(Nz::Vector3f::Zero()),
		m_nbQuads(0)
	{
		ResetMaterials(1);

		SetDefaultMaterial();
	}

	inline SlicedSprite::SlicedSprite(MaterialRef material) :
		SlicedSprite()
	{
		SetMaterial(std::move(material), true);
	}

	inline SlicedSprite::SlicedSprite(Texture* texture) :
		SlicedSprite()
	{
		SetTexture(texture, true);
	}

	inline const Color& SlicedSprite::GetColor() const
	{
		return m_color;
	}

	inline const Vector3f& SlicedSprite::GetOrigin() const
	{
		return m_origin;
	}

	inline const Vector2f& SlicedSprite::GetSize() const
	{
		return m_size;
	}

	inline const Rectf& SlicedSprite::GetTextureCoords() const
	{
		return m_textureCoords;
	}

	inline float SlicedSprite::GetTopSliceMargin() const
	{
		return m_topMargin;
	}

	inline float SlicedSprite::GetDownSliceMargin() const
	{
		return m_downMargin;
	}

	inline float SlicedSprite::GetLeftSliceMargin() const
	{
		return m_leftMargin;
	}

	inline float SlicedSprite::GetRightSliceMargin() const
	{
		return m_rightMargin;
	}

	inline void SlicedSprite::SetColor(const Color& color)
	{
		m_color = color;

		InvalidateVertices();
	}

	inline void SlicedSprite::SetDefaultMaterial()
	{
		MaterialRef material = Material::New();
		material->EnableFaceCulling(false);
		material->EnableScissorTest(true);

		SetMaterial(std::move(material));
	}

	inline void SlicedSprite::SetMaterial(MaterialRef material, bool resizeSprite)
	{
		SetMaterial(GetSkin(), std::move(material), resizeSprite);
	}

	inline void SlicedSprite::SetMaterial(std::size_t skinIndex, MaterialRef material, bool resizeSprite)
	{
		InstancedRenderable::SetMaterial(skinIndex, 0, std::move(material));

		if (resizeSprite)
		{
			if (const MaterialRef& newMat = GetMaterial())
			{
				const TextureRef& diffuseMap = newMat->GetDiffuseMap();
				if (diffuseMap && diffuseMap->IsValid())
					SetSize(Vector2f(Vector2ui(diffuseMap->GetSize())));
			}
		}
	}

	inline void SlicedSprite::SetOrigin(const Vector3f& origin)
	{
		m_origin = origin;

		// On invalide la bounding box
		InvalidateBoundingVolume();
		InvalidateVertices();
	}

	inline void SlicedSprite::SetSize(const Vector2f& size)
	{
		m_size = size;

		// On invalide la bounding box
		InvalidateBoundingVolume();
		InvalidateVertices();
	}

	inline void SlicedSprite::SetSize(float sizeX, float sizeY)
	{
		SetSize(Vector2f(sizeX, sizeY));
	}

	inline void SlicedSprite::SetTexture(TextureRef texture, bool resizeSprite)
	{
		SetTexture(GetSkin(), std::move(texture), resizeSprite);
	}

	inline void SlicedSprite::SetTexture(std::size_t skinIndex, TextureRef texture, bool resizeSprite)
	{
		const MaterialRef& material = GetMaterial(skinIndex);

		if (material->GetReferenceCount() > 1)
		{
			MaterialRef newMat = Material::New(*material); // Copy
			newMat->SetDiffuseMap(std::move(texture));

			SetMaterial(skinIndex, std::move(newMat), resizeSprite);
		}
		else
		{
			material->SetDiffuseMap(std::move(texture));
			const TextureRef& newTexture = material->GetDiffuseMap();

			if (resizeSprite && newTexture && newTexture->IsValid())
				SetSize(Vector2f(Vector2ui(newTexture->GetSize())));
		}
	}

	inline void SlicedSprite::SetTextureCoords(const Rectf& coords)
	{
		m_textureCoords = coords;

		InvalidateVertices();
	}

	inline void SlicedSprite::SetTextureRect(const Rectui& rect)
	{
		const MaterialRef& material = GetMaterial();
		NazaraAssert(material->HasDiffuseMap(), "Sprite material has no diffuse map");

		Texture* diffuseMap = material->GetDiffuseMap();

		float invWidth = 1.f / diffuseMap->GetWidth();
		float invHeight = 1.f / diffuseMap->GetHeight();

		SetTextureCoords(Rectf(invWidth * rect.x, invHeight * rect.y, invWidth * rect.width, invHeight * rect.height));
	}

	inline void SlicedSprite::SetSliceMargin(float size)
	{
		SetSliceMargin(size, size, size, size);
	}

	inline void SlicedSprite::SetSliceMargin(unsigned int size)
	{
		SetSliceMargin(size, size, size, size);
	}

	inline void SlicedSprite::SetSliceMargin(float top, float down, float left, float right)
	{
		m_topMargin = top;
		m_downMargin = down;
		m_leftMargin = left;
		m_rightMargin = right;

		InvalidateVertices();
	}

	inline void SlicedSprite::SetSliceMargin(unsigned int top, unsigned int down, unsigned int left, unsigned int right)
	{
		const MaterialRef& material = GetMaterial();
		NazaraAssert(material->HasDiffuseMap(), "Sprite material has no diffuse map");

		Texture* diffuseMap = material->GetDiffuseMap();

		float invWidth = 1.f / diffuseMap->GetWidth();
		float invHeight = 1.f / diffuseMap->GetHeight();

		SetSliceMargin(invWidth * top, invHeight * down, invWidth * left, invHeight * right);
	}

	inline SlicedSprite& SlicedSprite::operator=(const SlicedSprite& sprite)
	{
		InstancedRenderable::operator=(sprite);

		m_color = sprite.m_color;
		m_origin = sprite.m_origin;
		m_textureCoords = sprite.m_textureCoords;
		m_size = sprite.m_size;

		m_topMargin = sprite.m_topMargin;
		m_downMargin = sprite.m_downMargin;
		m_leftMargin = sprite.m_leftMargin;
		m_rightMargin = sprite.m_rightMargin;
		m_nbQuads = 0;

		// We do not copy final vertices because it's highly probable that our parameters are modified and they must be regenerated
		InvalidateBoundingVolume();
		InvalidateVertices();

		return *this;
	}

	inline void SlicedSprite::InvalidateVertices()
	{
		InvalidateInstanceData(0);
	}

	template<typename... Args>
	SlicedSpriteRef SlicedSprite::New(Args&&... args)
	{
		auto object = std::make_unique<SlicedSprite>(std::forward<Args>(args)...);
		object->SetPersistent(false);

		return object.release();
	}
}

#include <Nazara/Graphics/DebugOff.hpp>

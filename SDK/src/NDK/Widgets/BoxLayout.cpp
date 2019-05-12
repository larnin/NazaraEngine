// Copyright (C) 2017 Jérôme Leclercq
// This file is part of the "Nazara Development Kit"
// For conditions of distribution and use, see copyright notice in Prerequisites.hpp

#include <NDK/Widgets/BoxLayout.hpp>
#include <Nazara/Core/Log.hpp>
#include <Nazara/Core/MemoryHelper.hpp>
#include <cassert>

namespace Ndk
{
	void BoxLayout::OnLayout()
	{
		BaseWidget::OnLayout();

		std::size_t axis1, axis2;

		switch (m_orientation)
		{
			case BoxLayoutOrientation_Horizontal:
				axis1 = 0; //< x
				axis2 = 1; //< y
				break;

			case BoxLayoutOrientation_Vertical:
				axis1 = 1; //< y
				axis2 = 0; //< x
				break;

			default:
				assert(false);
				break;
		}

		m_childInfos.clear();

		// Handle size
		ForEachWidgetChild([&](BaseWidget* child)
		{
			if (!child->IsVisible())
				return;

			Nz::Vector2f scale(child->GetScale(Nz::CoordSys_Local));

			m_childInfos.emplace_back();
			auto& info = m_childInfos.back();
			info.isConstrained = false;
			info.maximumSize = child->GetMaximumSize()[axis1] * scale[axis1];
			info.minimumSize = child->GetMinimumSize()[axis1] * scale[axis1];
			info.preferedSize = child->GetPreferredSize()[axis1] * scale[axis1];
			info.size = info.minimumSize;
			info.widget = child;
		});

		Nz::Vector2f layoutSize = GetSize();

		float availableSpace = layoutSize[axis1] - m_spacing * (m_childInfos.size() - 1);
		float remainingSize = availableSpace;
		for (auto& info : m_childInfos)
			remainingSize -= info.minimumSize;

		// Okay this algorithm is FAR from perfect but I couldn't figure a way other than this one
		std::size_t unconstrainedChildCount = m_childInfos.size();

		bool hasUnconstrainedChilds = false;
		for (std::size_t i = 0; i < m_childInfos.size(); ++i)
		{
			if (remainingSize <= 0.0001f)
				break;

			float evenSize = remainingSize / unconstrainedChildCount;

			for (auto& info : m_childInfos)
			{
				if (info.isConstrained)
					continue;

				float previousSize = info.size;

				info.size += evenSize;
				if (info.size > info.maximumSize)
				{
					unconstrainedChildCount--;

					evenSize += (info.size - info.maximumSize) / unconstrainedChildCount;
					info.isConstrained = true;
					info.size = info.maximumSize;
				}
				else
					hasUnconstrainedChilds = true;

				remainingSize -= info.size - previousSize;
			}

			if (!hasUnconstrainedChilds)
				break;
		}

		float spacing = m_spacing + remainingSize / (m_childInfos.size() - 1);

		for (auto& info : m_childInfos)
		{
			Nz::Vector2f scale(info.widget->GetScale(Nz::CoordSys_Local));
			Nz::Vector2f newSize = info.widget->GetSize();
			newSize[axis1] = info.size / scale[axis1];
			newSize[axis2] = layoutSize[axis2] / scale[axis2];

			info.widget->Resize(newSize);
		}

		// Handle position
		float cursor = 0.f;
		bool first = true;
		for (auto& info : m_childInfos)
		{
			if (first)
				first = false;
			else
				cursor += spacing;

			Nz::Vector2f position = Nz::Vector2f(0.f, 0.f);
			position[axis1] = cursor;

			info.widget->SetPosition(position);

			cursor += info.size;
		};

		Nz::Vector2f preferedSize{ 0, 0 };

		for (const ChildInfo & info : m_childInfos)
			preferedSize[axis1] += info.preferedSize;
		if (!m_childInfos.empty())
			preferedSize[axis1] += m_spacing * (m_childInfos.size() - 1);
		preferedSize[axis2] = GetPreferredSize()[axis2];
		SetPreferredSize(preferedSize);
		SetMinimumSize(preferedSize);
	}
}

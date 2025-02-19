#pragma once
#include <vector>
#include <algorithm>
#include <Maths/Math.h>
#include <Rendering/Renderers/Storages/GraphicVertex.h>
#include <Rendering/Geometries/GeometryEnum.h>

namespace ZEngine::Rendering::Geometries
{

    /*Need to be deprecated*/
    struct IGeometry
    {
        IGeometry() = default;

        IGeometry(std::vector<Renderers::Storages::GraphicVertex>&& vertices) : m_vertices(std::move(vertices)) {}

        virtual ~IGeometry() = default;

        virtual void SetVertices(std::vector<Renderers::Storages::GraphicVertex>&& vertices)
        {
            m_vertices = std::move(vertices);
        }

        virtual const Maths::Matrix4& GetTransform() const
        {
            return m_transform;
        }

        virtual void SetTransform(const Maths::Matrix4& transform)
        {
            m_transform = transform;
        }

        virtual std::vector<Renderers::Storages::GraphicVertex>& GetVertices()
        {
            return m_vertices;
        }

        virtual GeometryType GetGeometryType() const
        {
            return m_geometry_type;
        }

    protected:
        Maths::Matrix4                                  m_transform{Maths::Matrix4(1.0f)};
        std::vector<Renderers::Storages::GraphicVertex> m_vertices{};
        GeometryType                                    m_geometry_type{GeometryType::CUSTOM};
    };
} // namespace ZEngine::Rendering::Geometries

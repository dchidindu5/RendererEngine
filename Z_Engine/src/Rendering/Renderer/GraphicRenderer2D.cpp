#pragma once
#include "GraphicRenderer2D.h"
#include "../Buffers/BufferLayout.h"
#include "../../Managers/ShaderManager.h"
#include "../../Managers/TextureManager.h"

#include "../Meshes/Rectangle.h"
#include "../Meshes/Triangle.h"

#include <memory>

using namespace Z_Engine::Rendering::Meshes;

using namespace Z_Engine::Rendering::Buffers::Layout;
using namespace Z_Engine::Managers;

namespace Z_Engine::Rendering::Renderer {


	void GraphicRenderer2D::Initialize() {
		GraphicRenderer::Initialize();
	
		ShaderManager::Load("src/Assets/Shaders/simple_mesh_2d.glsl");
		TextureManager::Add("default_texture", 1, 1);

		m_mesh_map.emplace("rectangle", Rectangle2D{});
		m_mesh_map.emplace("triangle", Triangle2D{});
	}

	void GraphicRenderer2D::DrawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color, float angle) {
		DrawRect({position.x, position.y, 0.0f}, size, color, angle);
	}

	void GraphicRenderer2D::DrawRect(const glm::vec3& position, const glm::vec2& size, const glm::vec3& color, float angle) {
		_DrawRect({position.x, position.y, position.z, 0.0f}, size, {color.r, color.g, color.b, 255}, angle);
	}

	void GraphicRenderer2D::DrawRect(const glm::vec2& position, const glm::vec2& size, float angle, const Z_Engine::Ref<Z_Engine::Rendering::Textures::Texture>& texture) {
		auto texture_2d = std::dynamic_pointer_cast<Z_Engine::Rendering::Textures::Texture2D>(texture);
		assert(texture_2d != nullptr);
		DrawRect(position, size, angle, texture_2d);
	}

	void GraphicRenderer2D::DrawRect(const glm::vec3& position, const glm::vec2& size, float angle, const Z_Engine::Ref<Z_Engine::Rendering::Textures::Texture>& texture) {
		auto texture_2d = std::dynamic_pointer_cast<Z_Engine::Rendering::Textures::Texture2D>(texture);
		assert(texture_2d != nullptr);
		DrawRect(position, size, angle, texture_2d);
	}

	void GraphicRenderer2D::DrawRect(const glm::vec2& position, const glm::vec2& size, float angle, const Z_Engine::Ref<Z_Engine::Rendering::Textures::Texture2D>& texture) {
		DrawRect({position.x, position.y, 0.0f}, size, angle, texture);
	}

	void GraphicRenderer2D::DrawRect(const glm::vec3& position, const glm::vec2& size, float angle, const Z_Engine::Ref<Z_Engine::Rendering::Textures::Texture2D>& texture) {
		_DrawRect({position.x, position.y, position.z, 0.0f}, size, angle, texture);
	}


	void GraphicRenderer2D::DrawRect(const glm::vec2& position, const glm::vec2& size, float angle, const Ref<Z_Engine::Rendering::Textures::Texture>& texture, const glm::vec4& tint_color, float tiling_factor) {
		auto texture_2d = std::dynamic_pointer_cast<Z_Engine::Rendering::Textures::Texture2D>(texture);
		assert(texture_2d != nullptr);
		DrawRect(position, size, angle, texture_2d, tint_color, tiling_factor);
	}
	
	void GraphicRenderer2D::DrawRect(const glm::vec3& position, const glm::vec2& size, float angle, const Ref<Z_Engine::Rendering::Textures::Texture>& texture, const glm::vec4& tint_color, float tiling_factor) {
		auto texture_2d = std::dynamic_pointer_cast<Z_Engine::Rendering::Textures::Texture2D>(texture);
		assert(texture_2d != nullptr);
		DrawRect(position, size, angle, texture_2d, tint_color, tiling_factor);
	}
	
	void GraphicRenderer2D::DrawRect(const glm::vec2& position, const glm::vec2& size, float angle, const Ref<Z_Engine::Rendering::Textures::Texture2D>& texture, const glm::vec4& tint_color, float tiling_factor){
		DrawRect({position.x, position.y, 0.0f}, size, angle, texture, tint_color, tiling_factor);
	}
	
	void GraphicRenderer2D::DrawRect(const glm::vec3& position, const glm::vec2& size, float angle, const Ref<Z_Engine::Rendering::Textures::Texture2D>& texture, const glm::vec4& tint_color, float tiling_factor) {
		_DrawRect({position.x, position.y, position.z, 0.0f}, size, angle, texture, tint_color, tiling_factor);
	}



	void GraphicRenderer2D::DrawTriangle(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color, float angle) {
		DrawTriangle({position.x, position.y, 0.0f}, size, color, angle);
	}

	void GraphicRenderer2D::DrawTriangle(const glm::vec3& position, const glm::vec2& size, const glm::vec3& color, float angle) {
		_DrawTriangle({position.x, position.y, position.z, 0.0f}, size, {color.r, color.g, color.b, 255.0f}, angle);
	}

	void GraphicRenderer2D::DrawTriangle(const glm::vec2& position, const glm::vec2& size, float angle, const Z_Engine::Ref<Z_Engine::Rendering::Textures::Texture>& texture) {
		auto texture_2d = std::dynamic_pointer_cast<Z_Engine::Rendering::Textures::Texture2D>(texture);
		assert(texture_2d != nullptr);
		DrawTriangle(position, size, angle, texture_2d);
	}

	void GraphicRenderer2D::DrawTriangle(const glm::vec3& position, const glm::vec2& size, float angle, const Z_Engine::Ref<Z_Engine::Rendering::Textures::Texture>& texture) {
		auto texture_2d = std::dynamic_pointer_cast<Z_Engine::Rendering::Textures::Texture2D>(texture);
		assert(texture_2d != nullptr);
		DrawTriangle(position, size, angle, texture_2d);
	}

	void GraphicRenderer2D::DrawTriangle(const glm::vec2& position, const glm::vec2& size, float angle, const Z_Engine::Ref<Z_Engine::Rendering::Textures::Texture2D>& texture) {
		DrawTriangle({ position.x, position.y, 0.0f }, size, angle, texture);
	}

	void GraphicRenderer2D::DrawTriangle(const glm::vec3& position, const glm::vec2& size, float angle, const Z_Engine::Ref<Z_Engine::Rendering::Textures::Texture2D>& texture) {
		_DrawTriangle({ position.x, position.y, position.z, 0.0f }, size, angle, texture);
	}



	void GraphicRenderer2D::DrawTriangle(const glm::vec2& position, const glm::vec2& size, float angle, const Ref<Z_Engine::Rendering::Textures::Texture>& texture, const glm::vec4& tint_color, float tiling_factor) {
		auto texture_2d = std::dynamic_pointer_cast<Z_Engine::Rendering::Textures::Texture2D>(texture);
		assert(texture_2d != nullptr);
		DrawTriangle(position, size, angle, texture_2d, tint_color, tiling_factor);
	}

	void GraphicRenderer2D::DrawTriangle(const glm::vec3& position, const glm::vec2& size, float angle, const Ref<Z_Engine::Rendering::Textures::Texture>& texture, const glm::vec4& tint_color, float tiling_factor) {
		auto texture_2d = std::dynamic_pointer_cast<Z_Engine::Rendering::Textures::Texture2D>(texture);
		assert(texture_2d != nullptr);
		DrawTriangle(position, size, angle, texture_2d, tint_color, tiling_factor);
	}

	void GraphicRenderer2D::DrawTriangle(const glm::vec2& position, const glm::vec2& size, float angle, const Ref<Z_Engine::Rendering::Textures::Texture2D>& texture, const glm::vec4& tint_color, float tiling_factor) {
		DrawTriangle({ position.x, position.y, 0.0f }, size, angle, texture, tint_color, tiling_factor);
	}

	void GraphicRenderer2D::DrawTriangle(const glm::vec3& position, const glm::vec2& size, float angle, const Ref<Z_Engine::Rendering::Textures::Texture2D>& texture, const glm::vec4& tint_color, float tiling_factor) {
		_DrawTriangle({ position.x, position.y, position.z, 0.0f }, size, angle, texture, tint_color, tiling_factor);
	}



	void GraphicRenderer2D::_DrawRect(const glm::vec4& position, const glm::vec2& size, const glm::vec4& color, float angle) {

		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z }) *
			glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 0.0f });

		auto& texture = TextureManager::Get("default_texture");
		texture->SetData(color.r, color.g, color.b, color.a);
		GraphicRenderer::Submit(m_mesh_map["rectangle"].GetStorage()->GetShader(), m_mesh_map["rectangle"].GetStorage()->GetVertexArray(), transform, texture);
	}

	void GraphicRenderer2D::_DrawRect(const glm::vec4& position, const glm::vec2& size, float angle, const Z_Engine::Ref<Z_Engine::Rendering::Textures::Texture2D>& texture) {
		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z }) *
			glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 0.0f });

		GraphicRenderer::Submit(m_mesh_map["rectangle"].GetStorage()->GetShader(), m_mesh_map["rectangle"].GetStorage()->GetVertexArray(), transform, texture);
	}

	void GraphicRenderer2D::_DrawRect(const glm::vec4& position, const glm::vec2& size, float angle, const Z_Engine::Ref<Z_Engine::Rendering::Textures::Texture2D>& texture, const glm::vec4& tint_color, float tiling_factor) {
		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z }) *
			glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 0.0f });

		GraphicRenderer::Submit(m_mesh_map["rectangle"].GetStorage()->GetShader(), m_mesh_map["rectangle"].GetStorage()->GetVertexArray(), transform, texture, tint_color, tiling_factor);
	}

	void GraphicRenderer2D::_DrawTriangle(const glm::vec4& position, const glm::vec2& size, const glm::vec4& color, float angle) {

		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z }) *
			glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 0.0f });

		auto& texture = TextureManager::Get("default_texture");
		texture->SetData(color.r, color.g, color.b, color.a);
		GraphicRenderer::Submit(m_mesh_map["triangle"].GetStorage()->GetShader(), m_mesh_map["triangle"].GetStorage()->GetVertexArray(), transform, texture);
	}

	void GraphicRenderer2D::_DrawTriangle(const glm::vec4& position, const glm::vec2& size, float angle, const Z_Engine::Ref<Z_Engine::Rendering::Textures::Texture2D>& texture) {
		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z }) *
			glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 0.0f });

		GraphicRenderer::Submit(m_mesh_map["triangle"].GetStorage()->GetShader(), m_mesh_map["triangle"].GetStorage()->GetVertexArray(), transform, texture);
	}

	void GraphicRenderer2D::_DrawTriangle(const glm::vec4& position, const glm::vec2& size, float angle, const Z_Engine::Ref<Z_Engine::Rendering::Textures::Texture2D>& texture, const glm::vec4& tint_color, float tiling_factor) {
		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z }) *
			glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 0.0f });

		GraphicRenderer::Submit(m_mesh_map["triangle"].GetStorage()->GetShader(), m_mesh_map["triangle"].GetStorage()->GetVertexArray(), transform, texture, tint_color, tiling_factor);
	}
}
#include "Engine.hpp"
#include "ImGui.hpp"


namespace pc {

	void Engine::addEditorHelper() {
		rendering.removeEditor();
		if (editor_mode) {
			scene.createEditorHelper();
			for (auto& i : scene.helper)
				rendering.addEditor(std::make_shared<sf::RectangleShape>(i), 0);
		}
	}

	void Engine::addSceneToRendering() {
		rendering.remove();

		for (auto& i : scene.objects) {
			if (i->type == 's' || i->type == 'm' || i->type == 'a')
				rendering.add(i->sprite, i->layer);
		}
	}


	void Engine::loadScene() {
		if (reload) {
			reload = false;
			return;
		}
		//Load the scene, the user set
		scene.reset();
		//TODO: Here would be a detection if we are in range...
		//...but we don't have one, so we do it immediately
		script.loadScene(scene, true);
	}



	void Engine::start() {
		ScriptEngine::EditorValues editor = script.getEditorConfig();
		rendering.createWindow(editor.title, editor.fullscreen, editor.solution);
		rendering.imgui_rendering(true);

		//Start our ScriptEngine. The set Scene will be loaded
		script.preInit();
		script.setScene(scene);
		script.setFunctions(std::bind(&Engine::addSceneToRendering, this), std::bind(&Engine::loadScene, this), std::bind(&Subtitle::setText, &subtitle, std::placeholders::_1));
		//TODO: This has to be done. We need to write the functions, that will do the work of Engine stuff directly, and then pass it here, to then bind it with Lua in the function
		script.bindFunctions();
		script.init();

		subtitle.setSettings(script.getSubtitleSettings());
		rendering.addGUI(subtitle.subtitle, 0);

		main();
	}


	void Engine::main() {
		while (rendering.isOpen()) {
			processEvents();


			rendering.imgui_rendering(editor_mode);
			if (editor_mode) {
				scene.helper_count *= 0;
				rendering.removeEditor();
				scene.createEditorHelper();
				for (auto& i : scene.helper)
					rendering.addEditor(std::make_shared<sf::RectangleShape>(i), 0);

				rendering.newImGuiWindow();
				if (ImGui::Begin("Editormodus")) {
					str = scene.makeLuaString();
					ImGui::InputTextMultiline("Lua String", str, str.size());

					ImGui::Separator();
					if (ImGui::CollapsingHeader("Scene Properties")) {
						if (ImGui::TreeNode("Objects")) {
							//TODO: Add right-click menue
							for (auto& i : scene.objects) {
								ImGui::PushID(i->name.data(), "hhh");
								std::string o_name = "Object (" + i->name + ")";
								if (ImGui::TreeNode(o_name.data())) {
									ImGui::InputText("Texture String ", i->texture_string, 256);
									int pos[3];
									pos[0] = static_cast<int>(i->get().getPosition().x);
									pos[1] = static_cast<int>(i->get().getPosition().y);
									pos[2] = i->layer;
									if (ImGui::InputInt3("Position ", pos)) {
										i->get().setPosition(static_cast<float>(pos[0]), static_cast<float>(pos[1]));
										i->layer = pos[2];
										addSceneToRendering();
									}
									bool hover = i->hasAction('h');
									bool look = i->hasAction('l');
									bool collect = i->hasAction('c');
									bool use = i->hasAction('u');
									if (collect == use && collect)
										use = false;
									ImGui::Checkbox("Hover", &hover);
									ImGui::SameLine();
									ImGui::Checkbox("Look", &look);
									ImGui::SameLine();
									if (ImGui::Checkbox("Collect", &collect))
										use = false;
									ImGui::SameLine();
									if (ImGui::Checkbox("Use", &use))
										collect = false;

									i->actions.clear();
									if (hover)
										i->actions.push_back('h');
									if (look)
										i->actions.push_back('l');
									if (collect)
										i->actions.push_back('c');
									if (use)
										i->actions.push_back('u');


									ImGui::TreePop();
								}
								ImGui::PopID();
							}
							ImGui::TreePop();
						}

					}
					if (ImGui::CollapsingHeader("Variables")) {
					}


				}
				ImGui::End();
				ImGui::EndFrame();
			}

			//Update Animations
			std::shared_ptr<Animation> a;
			for (auto& object : scene.objects) {
				switch (object->type) {
					case 'm':
						a = std::static_pointer_cast<MoveableObject>(object);
						break;
					case 'a':
						a = std::static_pointer_cast<AnimatedObject>(object);
						break;
					default:
						continue;
				}
				a->update(rendering.getTime());
			}

			//Update Subtitle
			subtitle.update(rendering.getWindowObject().getSize(), rendering.getTime());


			rendering.render();
		}
	}


	void Engine::processEvents() {
		//We do the callbacks if wanted
		while (!rendering.events.empty()) {
			sf::Event event = rendering.events.front();
			rendering.events.pop();
			switch (event.type) {
				case sf::Event::TextEntered:
				break;
				case sf::Event::KeyPressed:
				break;
				case sf::Event::KeyReleased:
				switch (event.key.code) {
					case sf::Keyboard::F3:
					if (event.key.shift) {
						reload = true;
						std::string scene_name = scene.name;
						script.init();
						script.setScene(scene_name);
						loadScene();
						subtitle.setSettings(script.getSubtitleSettings());

					} else { //Only F3
						editor_mode = !editor_mode;
						addEditorHelper();
					}
					break;
					case sf::Keyboard::P:
					if (!editor_mode)
						break;

					if (editor_editing == nullptr) { // No active Object --> make one object active;
						scene.objects.sort(scene.sort_objects_by_layer);
						for (auto& i : scene.objects) {
							if (((i->type == 's' || i->type == 'm' || i->type == 'a') && i->sprite->getGlobalBounds().contains(sf::Vector2f(mouse_pos))) || (i->type == 'c' && i->click->getGlobalBounds().contains(sf::Vector2f(mouse_pos)))) {
								editor_editing = i->sprite;
								cursor_offset = sf::Vector2f(mouse_pos.x - editor_editing->getGlobalBounds().left, mouse_pos.y - editor_editing->getGlobalBounds().top);
								break;
							}
						}
					} else // One active object --> deactivate Objectediting
						editor_editing = nullptr;

					break;
				}
				break;
				case sf::Event::MouseWheelMoved:
				break;
				case sf::Event::MouseWheelScrolled:
				break;
				case sf::Event::MouseButtonPressed:
				break;
				case sf::Event::MouseButtonReleased:
				{
					//We don't want to be anoyed by clicks if we are in any ImGuiWindow
					if (ImGui::IsAnyWindowFocused())
						break;

					mouse_pos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
					if (editor_editing != nullptr) {
						if (event.mouseButton.button == sf::Mouse::Button::Left)
							editor_editing = nullptr;
						break;
					}
					scene.objects.sort(scene.sort_objects_by_layer);
					for (auto& i : scene.objects) {
						if (((i->type == 's' || i->type == 'm' || i->type == 'a') && i->sprite->getGlobalBounds().contains(sf::Vector2f(mouse_pos))) || (i->type == 'c' && i->click->getGlobalBounds().contains(sf::Vector2f(mouse_pos)))) {
							switch (event.mouseButton.button) {
								case sf::Mouse::Button::Left:
								if (i->hasAction('u')) {
									script.call(scene, i->name, 'u');
									goto break_for;
								}
								if (i->hasAction('c')) {
									script.call(scene, i->name, 'c');
									goto break_for;
								}
								case sf::Mouse::Button::Right:
								if (i->hasAction('l')) {
									script.call(scene, i->name, 'l');
									goto break_for;
								}
							}
						}
					}
				}
			break_for:
				break;
				case sf::Event::MouseMoved: {
					mouse_pos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);

					if (editor_editing != nullptr) { // Just move the object around; We don't wan't beeing bortherd by this;
						editor_editing->setPosition(sf::Vector2f(mouse_pos) - cursor_offset);
						scene.helper_count *= 0;
						addEditorHelper();
					} else { // Be normal
						scene.objects.sort(scene.sort_objects_by_layer);
						for (auto& i : scene.objects) {
							if (i->hasAction('h')) {
								if (((i->type == 's' || i->type == 'm' || i->type == 'a') && i->sprite->getGlobalBounds().contains(sf::Vector2f(mouse_pos))) || (i->type == 'c' && i->click->getGlobalBounds().contains(sf::Vector2f(mouse_pos)))) {
									script.call(scene, i->name, 'h');
									break;
								}
							}
						}
					}
				}
											break;
				case sf::Event::MouseEntered:
				break;
				case sf::Event::MouseLeft:
				break;
				case sf::Event::JoystickButtonPressed:
				break;
				case sf::Event::JoystickButtonReleased:
				break;
				case sf::Event::JoystickMoved:
				break;
				case sf::Event::JoystickConnected:
				break;
				case sf::Event::JoystickDisconnected:
				break;
				case sf::Event::TouchBegan:
				break;
				case sf::Event::TouchMoved:
				break;
				case sf::Event::TouchEnded:
				break;
				case sf::Event::SensorChanged:
				break;
			}


		}

	}



}
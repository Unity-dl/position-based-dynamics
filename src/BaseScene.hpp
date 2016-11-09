#pragma once

#include <memory>
#include <functional>

#include <CL/cl.hpp>
#include <nanogui/nanogui.h>
#include <glm/glm.hpp>

namespace clgl {
    /// @brief An interface to some kind of simulation scene that can be rendered.
    /// @author Benjamin Wiberg
    class BaseScene {
    public:
        BaseScene(cl::Context &context, cl::Device &device, cl::CommandQueue &queue)
                : mContext(context), mDevice(device), mQueue(queue) {
        }

        /**
         * Virtual destructor to enable proper deletion of derived classes.
         */
        virtual ~BaseScene() {}

        /**
         * Adds this scene's specific GUI components.
         * @param screen The nanoGUI screen
         */
        virtual void addGUI(nanogui::Screen *screen) = 0;

        /**
         * Resets the scene to it's initial state.
         */
        virtual void reset() = 0;

        /**
         * Updates the scene (in some way), by taking a timestep of dt.
         * @param dt The delta time (in seconds) since last frame
         */
        virtual void update() = 0;

        /**
         * Renders the scene at its current state.
         */
        virtual void render() = 0;

        inline bool isKeyDown(int glfwKey) {
            return mIsKeyDownFunctor(glfwKey);
        }

        inline void setIsKeyDownFunctor(const std::function<bool(int)> &isKeyDownFunctor)  {
            mIsKeyDownFunctor = isKeyDownFunctor;
        }

        //////////////
        /// EVENTS ///
        //////////////

        virtual bool keyboardEvent(int key, int scancode, int action, int modifiers) { return false; };

        virtual bool mouseButtonEvent(const glm::ivec2 &p, int button, bool down, int modifiers) { return false; };

        virtual bool mouseMotionEvent(const glm::ivec2 &p, const glm::ivec2 &rel, int button, int modifiers) { return false; };

        virtual bool mouseDragEvent(const glm::ivec2 &p, const glm::ivec2 &rel, int button, int modifiers) { return false; };

        virtual bool scrollEvent(const glm::ivec2 &p, const glm::vec2 &rel) { return false; };

        virtual bool resizeEvent(const glm::ivec2 &p) { return false; }

    protected:
        cl::Context &mContext;

        cl::Device &mDevice;

        cl::CommandQueue &mQueue;

    private:
        std::function<bool(int)> mIsKeyDownFunctor;
    };
}
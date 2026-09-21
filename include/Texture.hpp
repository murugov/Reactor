#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <raylib.h>
#include <string>

namespace Graphic {

class Texture {
private:
    ::Texture2D raw_texture_{};
    bool is_loaded_ = false;

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---

    Texture() = default;

    explicit Texture(const std::string& file_path) {
        raw_texture_ = ::LoadTexture(file_path.c_str());
        is_loaded_ = static_cast<bool>(raw_texture_.id > 0);
    }

    // NOTE: Protection against double deletion in VRAM
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    
    // --- Move Constructor ---
    
    Texture(Texture&& other) noexcept {
        raw_texture_ = other.raw_texture_;
        is_loaded_ = other.is_loaded_;
        
        other.raw_texture_ = ::Texture2D{};
        other.is_loaded_ = false;
    }

    // --- Move Assignment Operator ---

    Texture& operator=(Texture&& other) noexcept {
        if (this != &other) {
            unload();
            
            raw_texture_ = other.raw_texture_;
            is_loaded_ = other.is_loaded_;
            
            other.raw_texture_ = ::Texture2D{};
            other.is_loaded_ = false;
        }
        return *this;
    }
    
    // --- Destructor ---
    
    // NOTE: RAII: The destructor automatically cleans up VRAM.
    ~Texture() {
        unload();
    }

    // -------------------------------------------------------------------------------
    // --- Getters ---

    int width()      const { return raw_texture_.width; }
    int height()     const { return raw_texture_.height; }
    bool is_loaded() const { return is_loaded_; }

    ::Texture2D get_raw() const { return raw_texture_; }
    
    // -------------------------------------------------------------------------------
    // --- Implementation Of Methods ---
    
    void unload() {
        if (is_loaded_) {
            ::UnloadTexture(raw_texture_);
            is_loaded_ = false;
        }
    }
    
};

}

#endif

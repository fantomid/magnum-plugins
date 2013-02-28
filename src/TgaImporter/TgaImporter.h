#ifndef Magnum_Trade_TgaImporter_TgaImporter_h
#define Magnum_Trade_TgaImporter_TgaImporter_h
/*
    Copyright © 2010, 2011, 2012 Vladimír Vondruš <mosra@centrum.cz>

    This file is part of Magnum.

    Magnum is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License version 3
    only, as published by the Free Software Foundation.

    Magnum is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License version 3 for more details.
*/

/** @file
 * @brief Class Magnum::Trade::TgaImporter::TgaImporter
 */

#include <Trade/AbstractImporter.h>

#ifndef DOXYGEN_GENERATING_OUTPUT
#ifdef _WIN32
    #ifdef TgaImporter_EXPORTS
        #define TGAIMPORTER_EXPORT __declspec(dllexport)
    #else
        #define TGAIMPORTER_EXPORT __declspec(dllimport)
    #endif
    #define TGAIMPORTER_LOCAL
#else
    #define TGAIMPORTER_EXPORT __attribute__ ((visibility ("default")))
    #define TGAIMPORTER_LOCAL __attribute__ ((visibility ("hidden")))
#endif
#endif

namespace Magnum { namespace Trade { namespace TgaImporter {

/** @brief TGA importer plugin */
class TGAIMPORTER_EXPORT TgaImporter: public AbstractImporter {
    public:
        /** @copydoc AbstractImporter::AbstractImporter() */
        TgaImporter(Corrade::PluginManager::AbstractPluginManager* manager = 0, const std::string& plugin = ""): AbstractImporter(manager, plugin), _image(nullptr) {}
        inline virtual ~TgaImporter() { close(); }

        inline Features features() const override { return Feature::OpenFile|Feature::OpenStream; }

        bool open(std::istream& in) override;
        bool open(const std::string& filename) override;
        void close() override;

        UnsignedInt image2DCount() const override { return _image ? 1 : 0; }
        ImageData2D* image2D(UnsignedInt id) override;

        #pragma pack(1)
        /** @brief TGA file header */
        /** @todoc Enable @c INLINE_SIMPLE_STRUCTS again when unclosed &lt;component&gt; in tagfile is fixed*/
        struct TGAIMPORTER_LOCAL Header {
            UnsignedByte    identsize;      /**< @brief Size of ID field that follows header (0) */
            UnsignedByte    colorMapType;   /**< @brief 0 = None, 1 = paletted */
            UnsignedByte    imageType;      /**< @brief 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle */
            UnsignedShort   colorMapStart;  /**< @brief First color map entry */
            UnsignedShort   colorMapLength; /**< @brief Number of colors */
            UnsignedByte    colorMapBpp;    /**< @brief Bits per palette entry */
            UnsignedShort   beginX;         /**< @brief %Image x origin */
            UnsignedShort   beginY;         /**< @brief %Image y origin */
            UnsignedShort   width;          /**< @brief %Image width */
            UnsignedShort   height;         /**< @brief %Image height */
            UnsignedByte    bpp;            /**< @brief Bits per pixel (8, 16, 24, 32) */
            UnsignedByte    descriptor;     /**< @brief %Image descriptor */
        };
        #pragma pack(8)

    private:
        ImageData2D* _image;
};

}}}

#endif

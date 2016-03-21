/* Copyright (c) 2014-2016 "Omnidome" by cr8tr
 * Dome Mapping Projection Software (http://omnido.me).
 * Omnidome was created by Michael Winkelmann aka Wilston Oreo (@WilstonOreo)
 *
 * This file is part of Omnidome.
 *
 * Omnidome is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <omni/canvas/Interface.h>

#include <omni/serialization/PropertyMap.h>

namespace omni {
    namespace canvas {
        Interface::Interface() {
            // Disable scaling and translation by default
            transform_.setTranslationEnabled(false);
            transform_.setScaleEnabled(false);
        }

        Interface::~Interface() {}

        /// Spectator's center of canvas (center of bounding box by default)
        QVector3D Interface::center() const
        {
            return (bounds().max() + bounds().min()) * 0.5;
        }

        /// Canvas radius (is half of size by default)
        qreal Interface::radius() const
        {
            return bounds().size().length() * 0.5;
        }

        AffineTransform const& Interface::transform() const {
            return transform_;
        }

        AffineTransform& Interface::transform() {
            return transform_;
        }

        void Interface::setTransform(AffineTransform const& _transform) {
            transform_ = _transform;
        }

        /// Transformation matrix for canvas
        QMatrix4x4 Interface::matrix() const
        {
            return transform_.matrix();
        }
        /// Write mapping to stream
        void Interface::toStream(QDataStream& _os) const {
            PropertyMap _map;
            _map("transform",transform_);
            _os << _map;
        }

        /// Read mapping from stream
        void Interface::fromStream(QDataStream& _is) {
            PropertyMap _map;
            _is >> _map;
            _map.get("transform",transform_);
        }
    }
}
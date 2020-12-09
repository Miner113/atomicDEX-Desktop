/******************************************************************************
 * Copyright © 2013-2019 The Komodo Platform Developers.                      *
 *                                                                            *
 * See the AUTHORS, DEVELOPER-AGREEMENT and LICENSE files at                  *
 * the top-level directory of this distribution for the individual copyright  *
 * holder information and the developer policies on copyright and licensing.  *
 *                                                                            *
 * Unless otherwise agreed in a custom licensing agreement, no part of the    *
 * Komodo Platform software, including this file may be copied, modified,     *
 * propagated or distributed except according to the terms contained in the   *
 * LICENSE file                                                               *
 *                                                                            *
 * Removal or modification of this copyright notice is prohibited.            *
 *                                                                            *
 ******************************************************************************/

#pragma once

//! Qt
#include <QObject>
#include <QVariant>

//! Deps
#include <boost/thread/synchronized_value.hpp>
#include <nlohmann/json_fwd.hpp>

//! Project Headers
#include <antara/gaming/ecs/system.hpp>

namespace atomic_dex
{
    class update_service_checker final : public QObject, public ag::ecs::pre_update_system<update_service_checker>
    {
        Q_OBJECT

        Q_PROPERTY(QVariant update_status READ get_update_status NOTIFY updateStatusChanged)

        //! Private typedefs
        using t_update_time_point = std::chrono::high_resolution_clock::time_point;
        using t_json_synchronized = boost::synchronized_value<nlohmann::json>;

        //! Private members
        t_json_synchronized m_update_status;
        t_update_time_point m_update_clock;

        //! Private API
        void fetch_update_status() noexcept;

      signals:
        void updateStatusChanged();

      public:
        //! Constructor
        explicit update_service_checker(entt::registry& registry, QObject* parent = nullptr);

        //! Destructor
        ~update_service_checker() noexcept final = default;

        //! Public override
        void update() noexcept final;

        /*//! Public API
        [[nodiscard]] nlohmann::json get_update_status() const noexcept;*/

        //! Properties
        [[nodiscard]] QVariant get_update_status() const noexcept;
    };
} // namespace atomic_dex

REFL_AUTO(type(atomic_dex::update_service_checker))

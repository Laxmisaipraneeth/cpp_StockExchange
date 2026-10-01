/*
@file order.h
@brief Defines the core order structure for the matching engine.

This header represents the fundamental data unit of the exchange. It encapsulates
all necessary attributes for various order types (limit, market, stop, etc.) in a
single, fixed-size structure to facilitate efficient memory management and
in-place mutation during the matching lifecycle.

To ensure low-latency performance and hardware cache efficiency, this structure is
trivially copyable and follows strict deterministic memory alignment, avoiding
virtual functions or dynamic dispatch to prevent vtable overhead and branching.
*/
#pragma once

#include <cstddef>
#include <type_traits>
#include "core/types.h"

namespace exchange::matching {

    struct Level;

    struct alignas(64) Order{
        core::OrderId id{0};
        core::Side side{core::Side::BUY};
        core::Price price{0};
        core::Quantity qty{0};
        core::Quantity original_qty{0};
        core::Quantity display_qty{0};
        core::Quantity hidden_qty{0};
        core::Timestamp timestamp{0};
        core::OrderType type{core::OrderType::LIMIT};
        core::OrderStatus status{core::OrderStatus::NEW};
        core::ParticipantId participant_id{0};
        core::Price trigger_price{0};
        core::Quantity peak_qty{0};
        Order *prev{nullptr};
        Order *next{nullptr};
        Level *parent_level{nullptr};

        [[nodiscard]] bool is_stop_order() const noexcept{
            return type == core::OrderType::STOP || type == core::OrderType::STOP_LIMIT;
        }
    };
    static_assert(sizeof(Order)<=128,
                "Order should stay compact enough for cache-friendly access.");
    static_assert(std::is_standard_layout_v<Order>);


}
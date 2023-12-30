//
// Created by George Ford on 12/30/23.
//

#ifndef GTD_CONCEPTS_HPP_
#define GTD_CONCEPTS_HPP_

#include <type_traits>
#include <string_view>

#include "GtdHelper.hpp"

template <typename Int>
concept Integral = std::is_integral_v<std::remove_reference_t<Int>>;

template <typename T>
concept OptionalInt = requires( T val )
{
    { val.value() } -> Integral;
    { *val } -> Integral;
};

template <typename T>
concept FromConstChar = std::is_convertible_v<T, std::string_view>;

template <typename T>
concept OptionalStr = requires( T val )
{
    { val.value() } -> FromConstChar;
    { *val } -> FromConstChar;
};

template <typename T>
concept OptionalTimePoint = requires( T val )
{
    { val.value() } -> time_point_t;
    { *val } -> time_point_t;
};

// GTDBASE CONCEPTS
/*****************************************************************************/
template <typename Gtd_t>
concept GtdBaseGetters = requires( Gtd_t gtd )
{
    { gtd.uniqueId() } -> OptionalInt;
    { gtd.name() } -> std::convertible_to<std::string_view>;
    { gtd.status() } -> std::same_as<gtd::Status>;
    { gtd.statusStr() } -> std::convertible_to<std::string_view>;
    { gtd.created() } -> std::same_as<time_point_t>;
    { gtd.createdStr() } -> std::convertible_to<std::string_view>;
    { gtd.modified() } -> std::same_as<time_point_t>;
    { gtd.modifiedStr() } -> std::convertible_to<std::string_view>;
    { gtd.parentId() } -> OptionalInt;
    { gtd.notes() } -> OptionalStr;
};

template <typename Gtd_t>
concept SetUniqueId = GtdBaseGetters<Gtd_t> &&
        requires( Gtd_t gtd, unique_id_t val )
        {
            { gtd.setUniqueId(val) };
        };

template <typename Gtd_t>
concept SetName = GtdBaseGetters<Gtd_t> &&
        requires( Gtd_t gtd, std::string_view val )
        {
            { gtd.setName(val) };
        };

template <typename Gtd_t>
concept SetStatus = GtdBaseGetters<Gtd_t> &&
        requires( Gtd_t gtd, gtd::Status val )
        {
            { gtd.setStatus(val) };
        };

template <typename Gtd_t>
concept SetStatusStr = GtdBaseGetters<Gtd_t> &&
        requires( Gtd_t gtd, std::string_view val )
        {
            { gtd.setStatusStr(val) };
        };

template <typename Gtd_t>
concept SetCreated = GtdBaseGetters<Gtd_t> &&
        requires( Gtd_t gtd, time_point_t tp )
        {
            { gtd.setCreated(tp) };
        };

template <typename Gtd_t>
concept SetCreatedStr = GtdBaseGetters<Gtd_t> &&
        requires( Gtd_t gtd, const std::string& tp )
        {
            { gtd.setCreatedStr(tp) };
        };

template <typename Gtd_t>
concept SetModified = GtdBaseGetters<Gtd_t> &&
        requires( Gtd_t gtd, time_point_t tp )
        {
            { gtd.setModified(tp) };
        };

template <typename Gtd_t>
concept SetModifiedStr = GtdBaseGetters<Gtd_t> &&
        requires( Gtd_t gtd, const std::string& tp )
        {
            { gtd.setModifiedStr(tp) };
        };

template <typename Gtd_t>
concept SetParentId = GtdBaseGetters<Gtd_t> &&
        requires( Gtd_t gtd, unique_id_t id )
        {
            { gtd.setParentId(id) };
        };

template <typename Gtd_t>
concept SetNotes = GtdBaseGetters<Gtd_t> &&
        requires( Gtd_t gtd, const std::string& notes )
        {
            { gtd.setNotes(notes) };
        };

template <typename Gtd_t>
concept IsGtdBase = GtdBaseGetters<Gtd_t> &&
        SetUniqueId<Gtd_t> &&
        SetName<Gtd_t> &&
        SetStatus<Gtd_t> &&
        SetStatusStr<Gtd_t> &&
        SetCreated<Gtd_t> &&
        SetCreatedStr<Gtd_t> &&
        SetModified<Gtd_t> &&
        SetModifiedStr<Gtd_t> &&
        SetParentId<Gtd_t> &&
        SetNotes<Gtd_t>;

// COMPLETABLE CONCEPTS
/*****************************************************************************/
template <typename Gtd_t>
concept CompletableGetters = IsGtdBase<Gtd_t> && requires( Gtd_t gtd )
{
    { (gtd.contextId()) } -> OptionalInt;
    { (gtd.deferred()) } -> OptionalTimePoint;
    { (gtd.deferredStr()) } -> OptionalStr;
    { gtd.due() } -> OptionalTimePoint;
    { gtd.dueStr() } -> OptionalStr;
    { gtd.isRepeating() } -> bool;
    { gtd.flagged() } -> bool;
    { gtd.repeatFrom() } -> gtd::RepeatFrom;
    { gtd.repeatFromStr() } -> std::string_view;
    { gtd.repeatSchedule() } -> std::string_view;
};

template <typename Gtd_t>
concept SetContextId = CompletableGetters<Gtd_t> &&
        requires( Gtd_t gtd, unique_id_t id, bool update )
        {
            { gtd.setContextId(id, update) };
        };

template <typename Gtd_t>
concept SetDeferred = CompletableGetters<Gtd_t> &&
        requires( Gtd_t gtd, time_point_t tp, bool update )
        {
            { gtd.setDeferred(tp, update) };
        };

template <typename Gtd_t>
concept SetDeferredStr = CompletableGetters<Gtd_t> &&
        requires( Gtd_t gtd, std::string_view tp, bool update )
        {
            { gtd.setDeferredStr(tp, update) };
        };

template <typename Gtd_t>
concept SetDue = CompletableGetters<Gtd_t> &&
        requires( Gtd_t gtd, time_point_t tp, bool update )
        {
            { gtd.setDue(tp, update) };
        };

template <typename Gtd_t>
concept SetDueStr = CompletableGetters<Gtd_t> &&
        requires( Gtd_t gtd, std::string_view tp, bool update )
        {
            { gtd.setDueStr(tp, update) };
        };

template <typename Gtd_t>
concept SetIsRepeating = CompletableGetters<Gtd_t> &&
        requires( Gtd_t gtd, int isRepeating, bool update )
        {
            { gtd.setIsRepeating(isRepeating, update) };
        };

template <typename Gtd_t>
concept SetFlagged = CompletableGetters<Gtd_t> &&
        requires( Gtd_t gtd, int flagged, bool update )
        {
            { gtd.setFlagged(flagged, update) };
        };

template <typename Gtd_t>
concept SetRepeatFrom = CompletableGetters<Gtd_t> &&
        requires( Gtd_t gtd, gtd::RepeatFrom repeatFrom, bool update )
        {
            { gtd.setRepeatFrom(repeatFrom, update) };
        };

template <typename Gtd_t>
concept SetRepeatFromStr = CompletableGetters<Gtd_t> &&
        requires( Gtd_t gtd, std::string_view repeatFrom, bool update )
        {
            { gtd.setRepeatFrom(repeatFrom, update) };
        };

template <typename Gtd_t>
concept SetRepeatSchedule = CompletableGetters<Gtd_t> &&
        requires( Gtd_t gtd, std::string_view schedule, bool update )
        {
            { gtd.setRepeatSchedule(schedule, update) };
        };

template <typename Gtd_t>
concept Completable_ = CompletableGetters<Gtd_t> &&
        SetContextId<Gtd_t> &&
        SetDeferred<Gtd_t> &&
        SetDeferredStr<Gtd_t> &&
        SetDue<Gtd_t> &&
        SetDueStr<Gtd_t> &&
        SetIsRepeating<Gtd_t> &&
        SetFlagged<Gtd_t> &&
        SetRepeatFrom<Gtd_t> &&
        SetRepeatFromStr<Gtd_t> &&
        SetRepeatSchedule<Gtd_t>;

// TASK CONCEPTS
/******************************************************************************/
template <typename Gtd_t>
concept TaskGetters = Completable_<Gtd_t> && requires( Gtd_t gtd )
{
    { gtd.projectId() } -> OptionalInt;
    { gtd.taskType() } -> gtd::TaskType;
};

template <typename Gtd_t>
concept SetProjectId = TaskGetters<Gtd_t> && requires( Gtd_t gtd, unique_id_t id, bool update )
{
    { gtd.setProjectId(id, update) };
};

template <typename Gtd_t>
concept SetTaskType = TaskGetters<Gtd_t> && requires( Gtd_t gtd, gtd::TaskType taskType, bool update )
{
    { gtd.setTaskType(taskType, update) };
};

template <typename Gtd_t>
concept SetTaskTypeStr = TaskGetters<Gtd_t> && requires( Gtd_t gtd, std::string_view taskType, bool update )
{
    { gtd.setTaskType(taskType, update) };
};

template<typename Gtd_t>
concept Task_ = TaskGetters<Gtd_t> &&
    SetProjectId<Gtd_t> &&
    SetTaskType<Gtd_t> &&
    SetTaskTypeStr<Gtd_t>;

#endif //GTD_CONCEPTS_HPP_

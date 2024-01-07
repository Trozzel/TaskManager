//
// Created by George Ford on 12/30/23.
//

#ifndef GTD_CONCEPTS_HPP_
#define GTD_CONCEPTS_HPP_

#include <__concepts/same_as.h>
#include <__ranges/concepts.h>
#include <string_view>

#include "GtdHelper.hpp"

template <typename Int>
concept Integral = std::is_integral_v<std::remove_reference_t<Int>>;

template <typename T>
concept StringType = std::is_convertible_v<T, std::string_view>;

// SQLITE TYPE CONCEPTS
template<typename T>
concept SqliteType = std::convertible_to<T, std::string_view> || 
	std::integral<T>;

// GTDBASE CONCEPTS
/*****************************************************************************/
template <typename Gtd_t>
concept GtdBaseGetters = requires( Gtd_t gtd )
{
    { gtd.uniqueId() } -> std::same_as<std::optional<unique_id_t>>;
    { gtd.name() } -> std::convertible_to<std::string_view>;
    { gtd.status() } -> std::same_as<gtd::Status>;
    { gtd.statusStr() } -> std::convertible_to<std::string_view>;
    { gtd.created() } -> std::same_as<time_point_t>;
    { gtd.createdStr() } -> std::convertible_to<std::string_view>;
    { gtd.modified() } -> std::same_as<time_point_t>;
    { gtd.modifiedStr() } -> std::convertible_to<std::string_view>;
    { gtd.parentId() } -> std::same_as<std::optional<unique_id_t>>;
    { gtd.notes() } -> std::same_as<std::optional<std::string_view>>;
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
            { gtd.setStatus(val) };
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
            { gtd.setCreated(tp) };
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
            { gtd.setModified(tp) };
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

// IMPLEMENTATION CLASS CONCEPTS
/******************************************************************************/
template <typename Gtd_t>
concept GtdImpl = IsGtdBase<Gtd_t> &&
        requires( Gtd_t )
        {
            { Gtd_t::tableName() } -> std::same_as<const char*>;
        };

template <typename Context_t>
concept IsContext = requires (gtd::GtdType gtdType) {
	gtdType == gtd::GtdType::Context;
	GtdImpl<Context_t>;
};

template <typename Folder_t>
concept IsFolder = requires (gtd::GtdType gtdType) {
	gtdType == gtd::GtdType::Folder;
	GtdImpl<Folder_t>;
};

template <typename GtdContainer>
concept GtdBaseRange = IsGtdBase<typename GtdContainer::value_type> &&
        std::ranges::range<GtdContainer>;

// COMPLETABLE CONCEPTS
/*****************************************************************************/
template <typename Gtd_t>
concept CompletableGetters = IsGtdBase<Gtd_t> &&
        requires( Gtd_t gtd )
        {
            { gtd.contextId() } -> std::same_as<std::optional<unique_id_t>>;
            { gtd.deferred() } -> std::same_as<std::optional<time_point_t>>;
            { gtd.deferredStr() } -> std::same_as<std::optional<std::string>>;
            { gtd.due() } -> std::same_as<std::optional<time_point_t>>;
            { gtd.dueStr() } -> std::same_as<std::optional<std::string>>;
            { gtd.isRepeating() } -> std::same_as<bool>;
            { gtd.flagged() } -> std::same_as<bool>;
            { gtd.repeatFrom() } -> std::same_as<gtd::RepeatFrom>;
            { gtd.repeatFromStr() } -> std::same_as<std::string_view>;
            { gtd.repeatSchedule() } -> std::same_as<std::string_view>;
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
            { gtd.setDeferred(tp, update) };
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
            { gtd.setDue(tp, update) };
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
concept IsCompletable = CompletableGetters<Gtd_t> &&
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
concept TaskGetters = IsCompletable<Gtd_t> &&
        requires( Gtd_t gtd )
        {
            { gtd.projectId() } -> std::same_as<std::optional<unique_id_t>>;
            { gtd.taskType() } -> std::same_as<gtd::TaskType>;
        };

template <typename Gtd_t>
concept SetProjectId = TaskGetters<Gtd_t> &&
        requires( Gtd_t gtd, unique_id_t id, bool update )
        {
            { gtd.setProjectId(id, update) };
        };

template <typename Gtd_t>
concept SetTaskType = TaskGetters<Gtd_t> &&
        requires( Gtd_t gtd, gtd::TaskType taskType, bool update )
        {
            { gtd.setTaskType(taskType, update) };
        };

template <typename Gtd_t>
concept SetTaskTypeStr = TaskGetters<Gtd_t> &&
        requires( Gtd_t gtd, std::string_view taskType, bool update )
        {
            { gtd.setTaskType(taskType, update) };
        };

template <typename Gtd_t>
concept IsTask = TaskGetters<Gtd_t> &&
        SetProjectId<Gtd_t> &&
        SetTaskType<Gtd_t> &&
        SetTaskTypeStr<Gtd_t>;

template <typename GtdContainer>
concept TaskRange = IsTask<typename GtdContainer::value_type> &&
        std::ranges::range<GtdContainer>;

// PROJECT CONCEPTS
/*****************************************************************************/
namespace gtd {
class Task;

template <typename T>
struct DummyContainer
{
    using value_type = T;
    T*
    begin() const;// {return tasks[0];}
    T*
    end() const;// {return tasks[0];}
};
}

template <typename Gtd_t>
concept GetTasks = requires( Gtd_t gtd, gtd::DummyContainer<gtd::Task> tasks )
{
    IsGtdBase<gtd::DummyContainer<gtd::Task>::value_type>;
    { gtd.getTasks(tasks) } -> std::ranges::range;
};

template <typename Gtd_t>
concept ProjectGetters = requires( Gtd_t gtd )
{
    { gtd.projectType() } -> std::same_as<gtd::ProjectType>;
    { gtd.folderId() } -> std::same_as<std::optional<unique_id_t>>;
    { gtd.completeWithLast() } -> std::same_as<bool>;
    { gtd.reviewSchedule() } -> std::same_as<std::string_view>;
};

template <typename Gtd_t>
concept SetTaskIds = ProjectGetters<Gtd_t> &&
        requires( Gtd_t gtd, gtd::DummyContainer<unique_id_t> taskIds )
        {
            { gtd.setTaskIds(taskIds) };
        };

template <typename Gtd_t>
concept AppendTaskId = ProjectGetters<Gtd_t> &&
        requires( Gtd_t gtd, unique_id_t taskId )
        {
            { gtd.appendTaskId(taskId) };
        };

template <typename Gtd_t>
concept AppendTaskIds = ProjectGetters<Gtd_t> &&
        requires( Gtd_t gtd, gtd::DummyContainer<unique_id_t> taskIds )
        {
            { gtd.appendTaskIds(taskIds) };
        };

template <typename Gtd_t>
concept SetProjectType = ProjectGetters<Gtd_t> &&
        requires( Gtd_t gtd, gtd::ProjectType pt, bool update )
        {
            { gtd.setProjectType(pt, update) };
        };

template <typename Gtd_t>
concept SetProjectTypeStr = ProjectGetters<Gtd_t> &&
        requires( Gtd_t gtd, std::string_view pt, bool update )
        {
            { gtd.setProjectType(pt, update) };
        };

template <typename Gtd_t>
concept SetFolderId = ProjectGetters<Gtd_t> &&
        requires( Gtd_t gtd, unique_id_t id, bool update )
        {
            { gtd.setFolderId(id, update) };
        };

template <typename Gtd_t>
concept SetCompleteWithLast = ProjectGetters<Gtd_t> &&
        requires( Gtd_t gtd, bool cwl, bool update )
        {
            { gtd.setCompleteWithLast(cwl, update) };
        };

template <typename Gtd_t>
concept SetReviewSchedule = ProjectGetters<Gtd_t> &&
        requires( Gtd_t gtd, std::string_view rs, bool update )
        {
            { gtd.setReviewSchedule(rs, update) };
        };

template <typename Gtd_t>
concept IsProject = ProjectGetters<Gtd_t> &&
        GetTasks<Gtd_t> &&
        SetTaskIds<Gtd_t> &&
        AppendTaskIds<Gtd_t> &&
        AppendTaskIds<Gtd_t> &&
        SetProjectType<Gtd_t> &&
        SetProjectTypeStr<Gtd_t> &&
        SetFolderId<Gtd_t> &&
        SetCompleteWithLast<Gtd_t> &&
        SetReviewSchedule<Gtd_t>;

// GTD CONTAINER CONCEPTS
/*****************************************************************************/
template <typename BaseContainer_t>
concept IsBaseContainer = std::ranges::range<BaseContainer_t> &&
    IsGtdBase<typename BaseContainer_t::value_type>;

template<typename ImplContainer_t>
concept IsImplContainer = std::ranges::range<ImplContainer_t> &&
	GtdImpl<typename ImplContainer_t::value_type>;

template <typename TaskContainer_t>
concept IsTaskContainer = std::ranges::range<TaskContainer_t> &&
    IsTask<typename TaskContainer_t::value_type>;

template <typename ProjectContainer_t>
concept IsProjectContainer = std::ranges::range<ProjectContainer_t> &&
	IsProject<typename ProjectContainer_t::range_value_t>;

// SANDBOX
/*****************************************************************************/
#endif //GTD_CONCEPTS_HPP_

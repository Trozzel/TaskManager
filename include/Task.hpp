//
// Created by George Ford on 1/28/22.
//

#ifndef GTD_TASK_HPP
#define GTD_TASK_HPP

#include <iostream>
#include <string>
#include <filesystem>

#include "GtdBase.hpp"
#include "GtdHelper.hpp"

namespace fs = std::__fs::filesystem;

namespace gtd {

class Task : public GtdBase {

private:
    ULL                  _contextId=0;
    ULL                  _projectId=0;
    std::string          _notes;
    time_point_t         _deferred = std::chrono::system_clock::now();
    time_point_t         _due = std::chrono::system_clock::now();
    TaskType             _taskType = TaskType::Parallel;
    bool                 _isRepeating = false;
    RepeatFrom           _repeatFrom = RepeatFrom::Due;
    fs::directory_entry  _repeatFromPath;

    // PRIVATE FUNCTIONS
    static TaskType strToTaskType(const std::string& taskTypeStr);

public:
    // CTORS
    explicit Task(const std::string & name = "");

    ~Task() override = default;

    // GETTERS
	inline ULL contextId() const;

	inline ULL projectId() const;
    
	[[nodiscard]] const std::string & notes() const;

    [[nodiscard]] const time_point_t & deferred() const;

    [[nodiscard]] const time_point_t & due() const;

    [[nodiscard]] TaskType taskType() const;

    [[nodiscard]] bool isIsRepeating() const;

    [[nodiscard]] RepeatFrom repeatFrom() const;

    [[nodiscard]] const fs::directory_entry &repeatFromPath() const;

    [[nodiscard]] const time_point_t &getDeferred() const;

    [[nodiscard]] bool isCompleteWithLast() const;

    [[nodiscard]] const fs::directory_entry &getRepeatFromPath() const;

    // SETTERS
	inline void setProjectId(ULL projectId);
	void setProjectId(const std::string & projectIdStr);

    void setContextId(ULL contextId);
    void setContextId(const std::string & contextIdStr);

    void setNotes(const std::string &notes);

    void setDeferred(const time_point_t &deferred);
    void setDeferred(const std::string & deferredStr);

    void setDue(const time_point_t &due);
    void setDue(const std::string & dueStr);

    void setTaskType(TaskType taskType);
    void setTaskType(const std::string & taskType);

    void setIsRepeating(bool isRepeating);
    void setIsRepeating(const std::string& isRepeating);

    void setRepeatFrom(RepeatFrom repeatFrom);
    void setRepeatFrom(const std::string & repeatFromStr);

    void setRepeatFromPath(const fs::directory_entry& dir);
    void setRepeatFromPath(const std::string& dir);

    friend std::ostream& operator<<(std::ostream& out, const Task& task);
};

} // namespace gtd


#endif //GTD_TASK_HPP

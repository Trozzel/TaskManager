#ifndef PROJECTS_HPP
#define PROJECTS_HPP

#include <string>
#include <list>
#include <initializer_list>

#include <fmt/format.h>

#include "Task.hpp"
#include "GtdBase.hpp"
#include "GtdHelper.hpp"

namespace gtd {

class Project : public GtdBase {

protected:
    ULL                  _contextId {};
    std::list<ULL>       _taskIds {};
    std::string          _notes {};
    time_point_t         _deferred {std::chrono::system_clock::now()};
    time_point_t         _due = std::chrono::system_clock::now();
    ProjectType          _projectType = ProjectType::Parallel;
    bool                 _completeWithLast=true;
    bool                 _isRepeating = false;
    RepeatFrom           _repeatFrom = RepeatFrom::Due;
    fs::directory_entry  _repeatFromPath {};

    // PRIVATE FUNCTIONS
    static ProjectType strToProjectType(const std::string& taskProjectStr);

public:
    // CTORS
    /**************************************************************************/
    // DEFAULT
    explicit Project(const std::string & name = "");

    ~Project() override = default;

    // GETTERS
	inline ULL contextId() const;

	[[nodiscard]] const std::string & notes() const;

    [[nodiscard]] const time_point_t & deferred() const;

    [[nodiscard]] const time_point_t & due() const;

    [[nodiscard]] ProjectType projectType() const;

    [[nodiscard]] bool isRepeating() const;

    [[nodiscard]] RepeatFrom repeatFrom() const;

    [[nodiscard]] const fs::directory_entry &repeatFromPath() const;

    [[nodiscard]] const time_point_t &getDeferred() const;

    [[nodiscard]] bool isCompleteWithLast() const;

    [[nodiscard]] const fs::directory_entry &getRepeatFromPath() const;

    // SETTERS
	void setTaskIds(const std::initializer_list<ULL> & taskIds);
	void setTaskIds(const std::list<ULL> & taskIds);
    template<typename Iter, typename T=ULL>
    void setTaskIds(Iter begin, Iter end);

    void appendTaskIds(const std::initializer_list<ULL> & taskIds);
	void appendTaskIds(const std::list<ULL> & taskIds);
    template<typename Iter, typename T=ULL>
    void appendTaskIds(Iter begin, Iter end);

    void appendTaskId(const std::string & taskIdStr);
    void appendTaskId(ULL taskId);

    void setContextId(ULL contextId);
    void setContextId(const std::string & contextIdStr);

    void setNotes(const std::string &notes);

    void setDeferred(const time_point_t &deferred);
    void setDeferred(const std::string & deferredStr);

    void setDue(const time_point_t &due);
    void setDue(const std::string & dueStr);

    void setProjectType(ProjectType projectType);
    void setProjectType(const std::string & projectType);

    void setCompleteWithLast(bool completeWithLast);
    void setCompleteWithLast(const std::string & completeWithLastStr);

    void setIsRepeating(bool isRepeating);
    void setIsRepeating(const std::string& isRepeating);

    void setRepeatFrom(RepeatFrom repeatFrom);
    void setRepeatFrom(const std::string & repeatFromStr);

    void setRepeatFromPath(const fs::directory_entry& dir);
    void setRepeatFromPath(const std::string& dir);

    friend std::ostream& operator<<(std::ostream& out, const Project& task);
};

template<typename Iter, typename T>
inline void Project::setTaskIds(Iter begin, Iter end) {
    _taskIds.clear();
    for(; begin != end; ++begin) {
        _taskIds.push_back(*begin);
    }
}

template<typename Iter, typename T>
inline void Project::appendTaskIds(Iter begin, Iter end) {
    for(; begin != end; ++begin) {
        _taskIds.push_back(*begin);
    }
}


} // namespace gtd

#endif // PROJECTS_HPP

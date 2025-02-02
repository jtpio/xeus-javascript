/***************************************************************************
* Copyright (c) 2024, Thorsten Beier
*
* Distributed under the terms of the BSD 3-Clause License.
*
* The full license is in the file LICENSE, distributed with this software.
****************************************************************************/


#ifndef XEUS_JAVASCRIPT_INTERPRETER_HPP
#define XEUS_JAVASCRIPT_INTERPRETER_HPP

#ifdef __GNUC__
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wattributes"
#endif

#include <string>
#include <memory>

#include "nlohmann/json.hpp"

#include "xeus_javascript_config.hpp"
#include "xeus/xinterpreter.hpp"


namespace nl = nlohmann;

namespace xeus_javascript
{

    void publish_stdout_stream(const std::string& message);
    void publish_stderr_stream(const std::string& message);
    void display_data(const std::string& json_str);
    void update_display_data(const std::string& json_str);

    void publish_execution_result(const std::string jstring);
    void publish_execution_error(const std::string jstring);


    class XEUS_JAVASCRIPT_API interpreter : public xeus::xinterpreter
    {
    public:

        interpreter();
        virtual ~interpreter() = default;

        inline std::string name()const
        {
            return "xjavascript";
        }

    protected:

        void configure_impl() override;

        nl::json execute_request_impl(int execution_counter,
                                      const std::string& code,
                                      bool silent,
                                      bool store_history,
                                      nl::json user_expressions,
                                      bool allow_stdin) override;

        nl::json complete_request_impl(const std::string& code, int cursor_pos) override;

        nl::json inspect_request_impl(const std::string& code,
                                      int cursor_pos,
                                      int detail_level) override;

        nl::json is_complete_request_impl(const std::string& code) override;

        nl::json kernel_info_request_impl() override;

        void shutdown_request_impl() override;

    };

    void export_xinterpreter();

}

#ifdef __GNUC__
    #pragma GCC diagnostic pop
#endif

#endif

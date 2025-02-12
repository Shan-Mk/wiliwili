//
// Created by fang on 2023/4/23.
//

#pragma once

#include <vector>
#include <map>
#include <string>
#include "borealis/views/dialog.hpp"
#include "utils/config_helper.hpp"

using namespace brls::literals;

namespace wiliwili {

// 用户id、{ 时间、内容 }
typedef std::map<std::string, std::vector<std::string>> BanList;

/**
 * 永久禁止使用名单
 * 涉及到人身攻击、言语羞辱等内容，永久不欢迎这些用户
 */
static BanList banList = {
    {"334039311", {"2023-04-22 09:30:23", "在作者视频发送弹幕：\"破解机滚吧\""}},
    {"1386247250", {"2022-10-03 14:22:43", "在作者视频发送评论，言语恶劣，内容概括为：\"未经调查评论作者为炒二手游戏机的贩子\""}},
    {"38806518", {"2022-09-04 19:42:10", "在作者视频发送评论：\"搞破解的剑宗。就你这还要啥支持？\""}},
};

/**
 * 提醒名单
 * 名单内用户在进入应用时会弹出提醒
 * 注：针对特定平台的发言，仅在特定平台客户端提醒
 */

#ifdef __SWITCH__
static BanList hintList = {
    {"3514445", {"2023-06-28 09:11:05", "在作者视频发送弹幕：\"有2k不看，拿720p看，没事吧\""}},
    {"34359982", {"2023-05-28 17:20:09", "在作者视频发送评论：\"我还是不理解，为啥不把手机掏出来看，这年头手机都没720p的吧。。。 我也有switch，纯纯的健身环启动器\""}},
    {"604953196", {"2023-05-12 06:51:23", "在作者视频发送弹幕：\"720p有意思吗\""}},
    {"5728203", {"2023-05-02 14:56:43", "在作者视频发送弹幕：\"虽然有挺好 但是拿手上不如手机，接电视不如直接用电视。。\""}},
    {"43465933", {"2023-04-19 17:11:00", "在作者视频发送弹幕：\"ns画质这么低都有人拿来看片啊\""}},
    {"40993847", {"2023-04-16 22:04:02", "在作者视频发送弹幕：\"这鬼东西你送我 我都不要\""}},
    {"310762077", {"2023-04-01 14:26:09", "在作者视频发送弹幕：\"手机不更方便吗？\""}},
    {"12463483", {"2022-09-29 05:46:28", "在作者视频发送弹幕：\"本末倒置游戏机不用来玩游戏看视频那要手机干嘛\""}},
    {"28480830", {"2022-09-25 13:51:40", "在作者视频发送弹幕：\"用手机比这玩意儿好多了，完全没有用啊\""}},
    {"97191935", {"2022-09-24 13:44:15", "在作者视频发送评论：\"所以说这是必须大气层后才能用的东西，你正儿八经做好了挂到商店卖1块钱不香么\""}},
    {"32254678", {"2022-09-24 13:16:07", "在作者视频发送弹幕：\"现在人手一部手机，还需要用游戏机看视频？\""}},
    {"1480776", {"2022-09-07 11:28:01", "在作者视频发送弹幕：\"不是什么好人笑死我了，自己做这个东西是为了什么还想不清楚\""}},
    {"406458700", {"2022-09-04 11:35:51", "在作者视频发送弹幕：\"主要是up推广破解机\""}},
    {"325042091", {"2022-12-06 20:01", "在作者视频发送评论：\"ns上B站不好用，卸载了。\""}},
    {"390053198", {"2022-11-28 00:07", "在作者视频发送评论：\"虽然但是，用ns看b站就那烂屏幕还不如用手机呢\""}},
    {"27472245", {"2022-11-22 12:10", "在作者视频发送评论：\"大屏手机的年代，谁捧着这么重的东西看视频？还各种小毛病，连接电视机看吧，但既然都有电视机了……何必呢\""}},
    {"487951303", {"2022-11-21 11:39", "在作者视频发送评论：\"没搞懂意义在哪儿？\""}},
};
#else
static BanList hintList = {
    {"9355679", {"2022-09-04 20:39:55", "在作者视频发送评论：\"wiliwili，这不是盗版是什么[辣眼睛]\""}},
};
#endif

static void checkBanList() {
    // 检查不欢迎名单
    std::string userid = ProgramConfig::instance().getUserID();
    if (wiliwili::banList.count(userid)) {
        brls::sync([userid]() {
            GA("ban", {{"user", userid},
                       {"version", APPVersion::instance().getVersionStr()},
                       {"git", APPVersion::instance().git_tag},
                       {"platform", APPVersion::instance().getPlatform()}})
            auto& data  = wiliwili::banList[userid];
            auto dialog = new brls::Dialog(fmt::format(
                "您于 {}\n{}\n现已被永久禁止使用本客户端", data[0], data[1]));
            dialog->setCancelable(false);
            dialog->addButton("hints/ok"_i18n,
                              []() { brls::Application::quit(); });
            dialog->open();
        });
    } else if (wiliwili::hintList.count(userid)) {
        brls::sync([userid]() {
            GA("ban", {{"user", userid},
                       {"version", APPVersion::instance().getVersionStr()},
                       {"git", APPVersion::instance().git_tag},
                       {"platform", APPVersion::instance().getPlatform()}})
            auto& data  = wiliwili::hintList[userid];
            auto dialog = new brls::Dialog(
                fmt::format("特此提醒\n您于 {}\n{}\n", data[0], data[1]));
            dialog->addButton("hints/ok"_i18n, []() {});
            dialog->open();
        });
    }
}

};  // namespace wiliwili

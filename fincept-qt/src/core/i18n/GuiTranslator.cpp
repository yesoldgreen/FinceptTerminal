#include "core/i18n/GuiTranslator.h"

#include "core/logging/Logger.h"
#include "storage/repositories/SettingsRepository.h"

#include <QAbstractButton>
#include <QAction>
#include <QApplication>
#include <QComboBox>
#include <QEvent>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMenu>
#include <QTabBar>
#include <QTableWidget>
#include <QTreeWidget>
#include <QWidget>

namespace fincept::i18n {

namespace {

constexpr auto kOrigTextProp = "_fincept_i18n_orig_text";
constexpr auto kOrigTitleProp = "_fincept_i18n_orig_title";
constexpr auto kOrigPlaceholderProp = "_fincept_i18n_orig_placeholder";
constexpr auto kOrigTooltipProp = "_fincept_i18n_orig_tooltip";
constexpr auto kOrigStatusTipProp = "_fincept_i18n_orig_status_tip";
constexpr auto kOrigComboItemsProp = "_fincept_i18n_orig_combo_items";
constexpr auto kOrigListItemsProp = "_fincept_i18n_orig_list_items";
constexpr auto kOrigTabItemsProp = "_fincept_i18n_orig_tab_items";
constexpr int kTableOrigTextRole = Qt::UserRole + 903;
constexpr int kTreeOrigTextRoleBase = Qt::UserRole + 913;

using Dictionary = QHash<QString, QString>;

const Dictionary& zh_cn_dictionary() {
    static const Dictionary dict = {
        {"Dashboard", "仪表盘"},
        {"Markets", "市场"},
        {"Crypto Trading", "加密交易"},
        {"Equity Trading", "股票交易"},
        {"Algo Trading", "算法交易"},
        {"Backtesting", "回测"},
        {"Portfolio", "投资组合"},
        {"Watchlist", "观察列表"},
        {"News", "新闻"},
        {"AI Chat", "AI 聊天"},
        {"Equity Research", "股票研究"},
        {"Economics", "经济"},
        {"AkShare Data", "AkShare 数据"},
        {"Asia Markets", "亚洲市场"},
        {"Geopolitics", "地缘政治"},
        {"Gov Data", "政府数据"},
        {"Maritime", "海事"},
        {"Prediction Markets", "预测市场"},
        {"Relationship Map", "关系图谱"},
        {"Derivatives", "衍生品"},
        {"Alt Investments", "另类投资"},
        {"M&A Analytics", "并购分析"},
        {"Surface Analytics", "曲面分析"},
        {"AI Quant Lab", "AI 量化实验室"},
        {"Agent Config", "智能体配置"},
        {"MCP Servers", "MCP 服务器"},
        {"Node Editor", "节点编辑器"},
        {"Code Editor", "代码编辑器"},
        {"Report Builder", "报告生成"},
        {"Trade Viz", "交易可视化"},
        {"Data Sources", "数据源"},
        {"Data Mapping", "数据映射"},
        {"File Manager", "文件管理"},
        {"Notes", "笔记"},
        {"Forum", "论坛"},
        {"Docs", "文档"},
        {"Support", "支持"},
        {"About", "关于"},
        {"Profile", "个人资料"},
        {"Settings", "设置"},
        {"Contact", "联系"},
        {"Terms", "条款"},
        {"Privacy", "隐私"},
        {"Trademarks", "商标"},
        {"Help", "帮助"},
        {"Credentials", "凭证"},
        {"Appearance", "外观"},
        {"Notifications", "通知"},
        {"Storage", "存储"},
        {"Storage & Cache", "存储与缓存"},
        {"Logging", "日志"},
        {"Security", "安全"},
        {"Profiles", "配置档"},
        {"Keybindings", "快捷键"},
        {"Python Environment", "Python 环境"},
        {"Developer", "开发者"},
        {"LLM Config", "LLM 配置"},
        {"Language", "语言"},
        {"Display Language", "界面语言"},
        {"English", "English"},
        {"简体中文", "简体中文"},
        {"LOCALIZATION", "本地化"},
        {"TYPOGRAPHY", "排版"},
        {"THEME", "主题"},
        {"INTERFACE", "界面"},
        {"Font Size", "字体大小"},
        {"Font Family", "字体"},
        {"Content Density", "内容密度"},
        {"Compact", "紧凑"},
        {"Default", "默认"},
        {"Comfortable", "舒适"},
        {"AI Chat Bubble", "AI 聊天气泡"},
        {"Ticker Bar", "行情条"},
        {"Animations", "动画"},
        {"Show AI Chat Bubble", "显示 AI 聊天气泡"},
        {"Show Ticker Bar", "显示行情条"},
        {"Enable Animations", "启用动画"},
        {"Save Settings", "保存设置"},
        {"Save", "保存"},
        {"Apply", "应用"},
        {"Cancel", "取消"},
        {"Close", "关闭"},
        {"Open", "打开"},
        {"Refresh", "刷新"},
        {"Search", "搜索"},
        {"Delete", "删除"},
        {"Create", "创建"},
        {"Add", "添加"},
        {"Remove", "移除"},
        {"Update", "更新"},
        {"Back", "返回"},
        {"Next", "下一步"},
        {"Continue", "继续"},
        {"Submit", "提交"},
        {"READY", "就绪"},
        {"BUSY", "忙碌"},
        {"ARTICLE DETAIL", "文章详情"},
        {"Select an article", "请选择一篇文章"},
        {"OPEN", "打开"},
        {"COPY URL", "复制链接"},
        {"ANALYZE", "分析"},
        {"ANALYZING...", "分析中..."},
        {"BOOKMARK", "收藏"},
        {"BOOKMARKED", "已收藏"},
        {"TRANSLATE", "翻译"},
        {"AI ANALYSIS", "AI 分析"},
        {"KEY POINTS", "要点"},
        {"RISK SIGNALS", "风险信号"},
        {"TOPICS", "主题"},
        {"MONITOR MATCHES", "监控命中"},
        {"RELATED", "相关内容"},
        {"ENTITIES", "实体"},
        {"NEARBY INFRASTRUCTURE", "附近基础设施"},
        {"No summary available.", "暂无摘要。"},
        {"No AI summary available.", "暂无 AI 摘要。"},
        {"First-Time Setup", "首次设置"},
        {"Login", "登录"},
        {"Register", "注册"},
        {"Forgot Password", "忘记密码"},
        {"Pricing", "定价"},
        {"Email", "邮箱"},
        {"Password", "密码"},
        {"Confirm Password", "确认密码"},
        {"Username", "用户名"},
        {"Name", "名称"},
        {"Phone", "电话"},
        {"Continue as Guest", "以访客身份继续"},
        {"Sign In", "登录"},
        {"Sign Up", "注册"},
        {"Reset Password", "重置密码"},
        {"Logout", "退出登录"},
        {"Floating chat assistant in the bottom-right corner.", "右下角悬浮 AI 助手。"},
        {"Live price ticker at the bottom of the screen.", "屏幕底部实时行情滚动条。"},
        {"Fade and transition effects throughout the UI.", "界面中的淡入淡出与过渡效果。"},
        {"Controls padding and spacing throughout the UI.", "控制整个界面的留白和间距。"},
        {"Change display language for the interface.", "切换应用界面的显示语言。"},
        {"General", "常规"},
        {"System", "系统"},
        {"Status", "状态"},
        {"Enabled", "已启用"},
        {"Disabled", "已禁用"},
        {"Connected", "已连接"},
        {"Disconnected", "未连接"},
        {"Error", "错误"},
        {"Warning", "警告"},
        {"Info", "信息"},
        {"Success", "成功"},
    };
    return dict;
}

QString stored_string(QObject* object, const char* property_name, const QString& current_value) {
    const QVariant existing = object->property(property_name);
    if (existing.isValid())
        return existing.toString();
    object->setProperty(property_name, current_value);
    return current_value;
}

QStringList stored_list(QObject* object, const char* property_name, const QStringList& current_value) {
    const QVariant existing = object->property(property_name);
    if (existing.isValid()) {
        const QStringList saved = existing.toStringList();
        if (saved.size() == current_value.size())
            return saved;
    }
    object->setProperty(property_name, current_value);
    return current_value;
}

QString translate_exact(const QString& original) {
    return zh_cn_dictionary().value(original, original);
}

QString translate_preserving_format(const QString& original) {
    if (original.isEmpty())
        return original;

    QString translated = translate_exact(original);
    if (translated != original)
        return translated;

    const QString trimmed = original.trimmed();
    if (trimmed != original) {
        translated = translate_exact(trimmed);
        if (translated != trimmed) {
            const int left_pad = original.indexOf(trimmed);
            const int right_pad = original.size() - left_pad - trimmed.size();
            return original.left(left_pad) + translated + original.right(right_pad);
        }
    }

    static const QString kTitleSep = QString::fromUtf8(" — ");
    if (original.contains(kTitleSep)) {
        QStringList parts = original.split(kTitleSep);
        for (QString& part : parts)
            part = translate_preserving_format(part);
        return parts.join(kTitleSep);
    }

    if (original.endsWith(':')) {
        const QString base = original.left(original.size() - 1);
        translated = translate_preserving_format(base);
        if (translated != base)
            return translated + ':';
    }

    if (original.endsWith("...")) {
        const QString base = original.left(original.size() - 3);
        translated = translate_preserving_format(base);
        if (translated != base)
            return translated + "...";
    }

    return original;
}

void apply_action_translation(QAction* action, bool zh) {
    if (!action)
        return;

    const QString orig_text = stored_string(action, kOrigTextProp, action->text());
    action->setText(zh ? translate_preserving_format(orig_text) : orig_text);

    const QString orig_tooltip = stored_string(action, kOrigTooltipProp, action->toolTip());
    action->setToolTip(zh ? translate_preserving_format(orig_tooltip) : orig_tooltip);

    const QString orig_status_tip = stored_string(action, kOrigStatusTipProp, action->statusTip());
    action->setStatusTip(zh ? translate_preserving_format(orig_status_tip) : orig_status_tip);
}

} // namespace

GuiTranslator& GuiTranslator::instance() {
    static GuiTranslator s;
    return s;
}

void GuiTranslator::initialize(QApplication* app) {
    if (initialized_ || !app)
        return;
    app_ = app;
    app_->installEventFilter(this);
    initialized_ = true;
}

void GuiTranslator::apply_saved_language() {
    auto r = fincept::SettingsRepository::instance().get("appearance.language", "en");
    set_language_code(r.is_ok() ? r.value() : "en");
}

void GuiTranslator::set_language_code(const QString& code) {
    const QString normalized = code.startsWith("zh", Qt::CaseInsensitive) ? "zh_CN" : "en";
    language_code_ = normalized;

    emit language_changed(language_code_);

    if (initialized_)
        apply_to_top_level_widgets();

    LOG_INFO("GuiTranslator", "GUI language set to " + language_code_);
}

bool GuiTranslator::is_simplified_chinese() const {
    return language_code_.startsWith("zh", Qt::CaseInsensitive);
}

QString GuiTranslator::translate_text(const QString& text) const {
    if (!is_simplified_chinese())
        return text;
    return translate_preserving_format(text);
}

bool GuiTranslator::eventFilter(QObject* watched, QEvent* event) {
    if (!initialized_ || !watched || !event)
        return QObject::eventFilter(watched, event);

    switch (event->type()) {
    case QEvent::Show:
    case QEvent::Polish:
    case QEvent::ChildAdded:
    case QEvent::WindowTitleChange:
    case QEvent::ToolTipChange:
    case QEvent::StatusTipChange:
        apply_to_object(watched);
        if (auto* widget = qobject_cast<QWidget*>(watched))
            apply_to_widget_tree(widget);
        break;
    default:
        break;
    }

    return QObject::eventFilter(watched, event);
}

void GuiTranslator::apply_to_top_level_widgets() {
    if (!app_)
        return;

    for (QWidget* widget : app_->topLevelWidgets()) {
        if (!widget)
            continue;
        apply_to_object(widget);
        apply_to_widget_tree(widget);
    }
}

void GuiTranslator::apply_to_widget_tree(QWidget* root) {
    if (!root)
        return;

    const auto children = root->findChildren<QObject*>();
    for (QObject* child : children)
        apply_to_object(child);
}

void GuiTranslator::apply_to_object(QObject* object) {
    if (!object)
        return;

    const bool zh = is_simplified_chinese();

    if (auto* label = qobject_cast<QLabel*>(object)) {
        const QString orig = stored_string(label, kOrigTextProp, label->text());
        label->setText(zh ? translate_preserving_format(orig) : orig);
    }

    if (auto* button = qobject_cast<QAbstractButton*>(object)) {
        const QString orig = stored_string(button, kOrigTextProp, button->text());
        button->setText(zh ? translate_preserving_format(orig) : orig);
    }

    if (auto* group = qobject_cast<QGroupBox*>(object)) {
        const QString orig = stored_string(group, kOrigTitleProp, group->title());
        group->setTitle(zh ? translate_preserving_format(orig) : orig);
    }

    if (auto* line_edit = qobject_cast<QLineEdit*>(object)) {
        const QString orig_placeholder =
            stored_string(line_edit, kOrigPlaceholderProp, line_edit->placeholderText());
        line_edit->setPlaceholderText(zh ? translate_preserving_format(orig_placeholder) : orig_placeholder);
    }

    if (auto* combo = qobject_cast<QComboBox*>(object)) {
        QStringList current_items;
        current_items.reserve(combo->count());
        for (int i = 0; i < combo->count(); ++i)
            current_items.append(combo->itemText(i));
        const QStringList orig_items = stored_list(combo, kOrigComboItemsProp, current_items);
        for (int i = 0; i < orig_items.size(); ++i)
            combo->setItemText(i, zh ? translate_preserving_format(orig_items[i]) : orig_items[i]);
    }

    if (auto* list = qobject_cast<QListWidget*>(object)) {
        QStringList current_items;
        current_items.reserve(list->count());
        for (int i = 0; i < list->count(); ++i)
            current_items.append(list->item(i)->text());
        const QStringList orig_items = stored_list(list, kOrigListItemsProp, current_items);
        for (int i = 0; i < orig_items.size(); ++i)
            list->item(i)->setText(zh ? translate_preserving_format(orig_items[i]) : orig_items[i]);
    }

    if (auto* tabbar = qobject_cast<QTabBar*>(object)) {
        QStringList current_items;
        current_items.reserve(tabbar->count());
        for (int i = 0; i < tabbar->count(); ++i)
            current_items.append(tabbar->tabText(i));
        const QStringList orig_items = stored_list(tabbar, kOrigTabItemsProp, current_items);
        for (int i = 0; i < orig_items.size(); ++i)
            tabbar->setTabText(i, zh ? translate_preserving_format(orig_items[i]) : orig_items[i]);
    }

    if (auto* menu = qobject_cast<QMenu*>(object)) {
        const QString orig_title = stored_string(menu, kOrigTitleProp, menu->title());
        menu->setTitle(zh ? translate_preserving_format(orig_title) : orig_title);
        for (QAction* action : menu->actions())
            apply_action_translation(action, zh);
    }

    if (auto* table = qobject_cast<QTableWidget*>(object)) {
        for (int col = 0; col < table->columnCount(); ++col) {
            if (auto* item = table->horizontalHeaderItem(col)) {
                QString orig = item->data(kTableOrigTextRole).toString();
                if (orig.isEmpty()) {
                    orig = item->text();
                    item->setData(kTableOrigTextRole, orig);
                }
                item->setText(zh ? translate_preserving_format(orig) : orig);
            }
        }
    }

    if (auto* tree = qobject_cast<QTreeWidget*>(object)) {
        if (auto* item = tree->headerItem()) {
            for (int col = 0; col < tree->columnCount(); ++col) {
                const int role = kTreeOrigTextRoleBase + col;
                QString orig = item->data(col, role).toString();
                if (orig.isEmpty()) {
                    orig = item->text(col);
                    item->setData(col, role, orig);
                }
                item->setText(col, zh ? translate_preserving_format(orig) : orig);
            }
        }
    }

    if (auto* widget = qobject_cast<QWidget*>(object)) {
        const QString orig_title = stored_string(widget, kOrigTitleProp, widget->windowTitle());
        widget->setWindowTitle(zh ? translate_preserving_format(orig_title) : orig_title);

        const QString orig_tooltip = stored_string(widget, kOrigTooltipProp, widget->toolTip());
        widget->setToolTip(zh ? translate_preserving_format(orig_tooltip) : orig_tooltip);

        const QString orig_status_tip = stored_string(widget, kOrigStatusTipProp, widget->statusTip());
        widget->setStatusTip(zh ? translate_preserving_format(orig_status_tip) : orig_status_tip);

        for (QAction* action : widget->actions())
            apply_action_translation(action, zh);
    }
}

} // namespace fincept::i18n

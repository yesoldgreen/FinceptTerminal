#pragma once

#include <QEvent>
#include <QObject>
#include <QString>

class QApplication;
class QWidget;

namespace fincept::i18n {

class GuiTranslator : public QObject {
    Q_OBJECT
  public:
    static GuiTranslator& instance();

    void initialize(QApplication* app);
    void apply_saved_language();
    void set_language_code(const QString& code);

    QString current_language_code() const { return language_code_; }
    bool is_simplified_chinese() const;

    QString translate_text(const QString& text) const;
    void apply_to_top_level_widgets();

  signals:
    void language_changed(const QString& language_code);

  protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

  private:
    GuiTranslator() = default;

    void apply_to_widget_tree(QWidget* root);
    void apply_to_object(QObject* object);

    QApplication* app_ = nullptr;
    QString language_code_ = "en";
    bool initialized_ = false;
    bool applying_ = false;
};

} // namespace fincept::i18n

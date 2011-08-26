/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

#ifndef __ctkPopupWidget_h
#define __ctkPopupWidget_h

// CTK includes
#include "ctkBasePopupWidget.h"

class ctkPopupWidgetPrivate;

/// Description:
class CTK_WIDGETS_EXPORT ctkPopupWidget : public ctkBasePopupWidget
{
  Q_OBJECT

  /// Control whether the popup listens to the application and baseWidget
  /// events and decides if it needs to be permanently or temporarily hidden.
  /// You might want to setActive(false) when embedding the popup
  /// into a static layout intead of having it top-level (no parent).
  /// Consider also removing its windowFlags (Qt::ToolTip |
  /// Qt::FramelessWindowHint) and removing the baseWidget.
  /// True by default
  Q_PROPERTY( bool active READ isActive WRITE setActive)

  /// Control wether the popup automatically opens when the mouse
  /// enter the widget. True by default
  Q_PROPERTY( bool autoShow READ autoShow WRITE setAutoShow)

  /// Control wether the popup automatically closes when the mouse
  /// leaves the widget. True by default
  Q_PROPERTY( bool autoHide READ autoHide WRITE setAutoHide)

public:
  typedef ctkBasePopupWidget Superclass;
  explicit ctkPopupWidget(QWidget* parent = 0);
  virtual ~ctkPopupWidget();

  /// Widget the popup is attached to. It opens right under \a baseWidget
  /// and if the ctkPopupWidget sizepolicy contains the growFlag/shrinkFlag,
  /// it tries to resize itself to fit the same width of \a baseWidget.
  virtual void setBaseWidget(QWidget* baseWidget);

  bool isActive()const;
  void setActive(bool);

  bool autoShow()const;
  /// Calling setAutoShow automatically updates opens the popup if the cursor
  /// is above the popup or the base widget.
  void setAutoShow(bool);

  bool autoHide()const;
  /// Don't automatically close the popup when leaving the widget.
  /// Calling setAutoHide automatically updates the state close the popup
  /// if the mouse is not over the popup nor the base widget.
  void setAutoHide(bool autoHide);

public slots:
  /// Convenient function that calls setAutoHide(!pin) and opens the popup
  /// if pin is true regardless of the value of \a AutoShow.
  /// It is typically connected with a checkable button to anchor the popup.
  void pinPopup(bool pin);

public:
  /// Reimplemented for internal reasons
  virtual void hidePopup();

protected:
  virtual void leaveEvent(QEvent* event);
  virtual void enterEvent(QEvent* event);
  virtual bool eventFilter(QObject* obj, QEvent* event);

protected slots:
  void updatePopup();
  virtual void onEffectFinished();

private:
  Q_DECLARE_PRIVATE(ctkPopupWidget);
  Q_DISABLE_COPY(ctkPopupWidget);
};

#endif

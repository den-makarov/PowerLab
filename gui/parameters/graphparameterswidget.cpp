#include <cmath>

#include <QComboBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QApplication>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QColorDialog>
#include <QSpinBox>
#include <QDoubleSpinBox>

#include "graphparameterswidget.h"
#include "graphs/graphwidget.h"
#include "graphs/graphparametersmodel.h"
#include "utils/math_utils.h"
#include "logger.h"

namespace PowerLab {
namespace Gui {

GraphParametersWidget::GraphParametersWidget(QWidget *parent, std::vector<GraphWidget*> graphs)
  : ParametersWidget(parent)
  , m_graphs(graphs)
{
  m_grid = new QGridLayout;
  m_grid->setAlignment(Qt::AlignTop);
  setLayout(m_grid);

  createGraphSelector();
  createPlotColorControls();
  createPlotGridControls();
  createGraphDataControls();

  updateView();
}

void GraphParametersWidget::updateGraphList(std::vector<GraphWidget*> graphs) {
  m_graphs = graphs;
  updateView();
  emit graphListUpdated();
}

void GraphParametersWidget::addHorizontalSeparator(int rowIndex) {
  QFrame *line = new QFrame;
  line->setFrameShape(QFrame::HLine);
  line->setFrameShadow(QFrame::Sunken);
  m_grid->addWidget(line, rowIndex, 0, 1, -1);
  m_layoutElements.push_back(line);
}

void GraphParametersWidget::createGraphSelector() {
  QLabel* graphSelectorLabel = new QLabel(tr("Graph selector"));

  m_graphSelector = new QComboBox;
  for(size_t idx = 0; idx < m_graphs.size(); idx++) {
    auto graph = m_graphs[idx];
    m_graphSelector->addItem(graph->objectName(), QVariant::fromValue(idx));
  }

  connect(m_graphSelector, QOverload<int>::of(&QComboBox::currentIndexChanged),
          this, &GraphParametersWidget::graphSelectorChanged);

  m_grid->addWidget(graphSelectorLabel, 0, 0, 1, -1);
  m_grid->addWidget(m_graphSelector, 1, 0, 1, -1);
  addHorizontalSeparator(2);
}

void GraphParametersWidget::createPlotColorControls() {
  m_bgColorButton = new QPushButton(tr("Background color"));
  connect(m_bgColorButton, &QPushButton::clicked, [this](bool /*Not interested*/){
    this->colorControlRequested(ColorControl::BACKGROUND_COLOR);
  });

  m_grid->addWidget(m_bgColorButton, 3, 0);

  m_gridColors = new QPushButton(tr("Grid color"));
  connect(m_gridColors, &QPushButton::clicked, [this](bool /*Not interested*/){
    this->colorControlRequested(ColorControl::GRID_LINES_COLOR);
  });

  m_grid->addWidget(m_gridColors, 3, 1);
  addHorizontalSeparator(4);

  m_layoutElements.push_back(m_bgColorButton);
  m_layoutElements.push_back(m_gridColors);
}

void GraphParametersWidget::addLabel(const QString& text, int row, int column) {
  QLabel* label = new QLabel(text);
  m_grid->addWidget(label, row, column);
  m_layoutElements.push_back(label);
}

void GraphParametersWidget::createPlotGridControls() {
  m_isAutoGrid = new QCheckBox("Auto grid");
  m_isAutoGrid->setChecked(true);

  connect(m_isAutoGrid, &QCheckBox::stateChanged,
          this, &GraphParametersWidget::autoGridChanged);

  m_grid->addWidget(m_isAutoGrid, 5, 0, 1, -1);
  m_layoutElements.push_back(m_isAutoGrid);

  addLabel(tr("H min"), 6, 0);
  m_hMin = new QDoubleSpinBox;
  m_hMin->setRange(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max());
  connect(m_hMin, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          [this](double value){
    this->updateGridLinesRange(value, SideControl::HORIZONTAL_MIN);
  });

  m_grid->addWidget(m_hMin, 6, 1);
  m_manualGridControls.push_back(m_hMin);

  addLabel(tr("H max"), 7, 0);
  m_hMax = new QDoubleSpinBox;
  m_hMax->setRange(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max());
  connect(m_hMax, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          [this](double value){
    this->updateGridLinesRange(value, SideControl::HORIZONTAL_MAX);
  });

  m_grid->addWidget(m_hMax, 7, 1);
  m_manualGridControls.push_back(m_hMax);

  addLabel(tr("H lines"), 8, 0);
  m_hLines = new QSpinBox;
  m_hLines->setRange(0, 40);
  m_hLines->setSingleStep(1);
  connect(m_hLines, QOverload<int>::of(&QSpinBox::valueChanged),
          [this](int value){
    this->updateGridLinesNumber(value, true);
  });

  m_grid->addWidget(m_hLines, 8, 1);
  m_manualGridControls.push_back(m_hLines);

  addLabel(tr("V min"), 9, 0);
  m_vMin = new QDoubleSpinBox;
  m_vMin->setRange(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max());
  connect(m_vMin, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          [this](double value){
    this->updateGridLinesRange(value, SideControl::VERTICAL_MIN);
  });

  m_grid->addWidget(m_vMin, 9, 1);
  m_manualGridControls.push_back(m_vMin);

  addLabel(tr("V max"), 10, 0);
  m_vMax = new QDoubleSpinBox;
  m_vMax->setRange(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max());
  connect(m_vMax, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          [this](double value){
    this->updateGridLinesRange(value, SideControl::VERTICAL_MAX);
  });

  m_grid->addWidget(m_vMax, 10, 1);
  m_manualGridControls.push_back(m_vMax);

  addLabel(tr("V lines"), 11, 0);
  m_vLines = new QSpinBox;
  m_vLines->setRange(0, 40);
  m_vLines->setSingleStep(1);
  connect(m_vLines, QOverload<int>::of(&QSpinBox::valueChanged),
          [this](int value){
    this->updateGridLinesNumber(value, false);
  });

  m_grid->addWidget(m_vLines, 11, 1);
  m_manualGridControls.push_back(m_vLines);
}

void GraphParametersWidget::setManualGridControlsEnabled(bool enabled) {
  for(auto item : m_manualGridControls) {
    item->setEnabled(enabled);
  }
}

void GraphParametersWidget::createGraphDataControls() {

}

void GraphParametersWidget::updateView() {
  m_graphSelector->clear();
  for(size_t idx = 0; idx < m_graphs.size(); idx++) {
    auto graph = m_graphs[idx];
    m_graphSelector->addItem(graph->objectName(), QVariant::fromValue(idx));
  }

  auto focusedGraphIdx = findFocusedGraphIdx();
  if(focusedGraphIdx != NO_GRAPH_FOCUSED) {
    m_graphSelector->setCurrentIndex(focusedGraphIdx);
    updateGraphParametersView(m_graphs[static_cast<size_t>(focusedGraphIdx)]);
    setGraphParametersVisible(true);
  } else {
    setGraphParametersVisible(false);
  }
}

void GraphParametersWidget::setGraphParametersVisible(bool visible) {
  for(auto item : m_layoutElements) {
    item->setVisible(visible);
  }

  for(auto item : m_manualGridControls) {
    item->setVisible(visible);
  }
}

int GraphParametersWidget::findFocusedGraphIdx() const {
  int focusedGraphIdx = NO_GRAPH_FOCUSED;

  if(m_graphs.size() != 0) {
    focusedGraphIdx = 0;
    auto focusedWidget = qApp->focusWidget();

    for(auto graph : m_graphs) {
      if(graph == focusedWidget) {
        break;
      }
      focusedGraphIdx++;
    }

    if(static_cast<size_t>(focusedGraphIdx) >= m_graphs.size()) {
      focusedGraphIdx = 0;
    }
  }

  return focusedGraphIdx;
}

void GraphParametersWidget::updateGraphParametersView(GraphWidget* graph) {
  if(!graph) {
    setGraphParametersVisible(false);
    return;
  }

  GraphParametersModel model(*graph);

  updateGridColors(model);
  updateGridLines(model);
  updateGraphData(model);
}

void GraphParametersWidget::updateGridColors(const GraphParametersModel& model) {
  m_bgColorButton->setPalette(model.getBackgroundColor());
  m_bgColorButton->setAutoFillBackground(true);

  m_gridColors->setPalette((model.getGridLinesColor()));
  m_gridColors->setAutoFillBackground(true);
}

void GraphParametersWidget::updateGridLines(const GraphParametersModel& model) {
  m_isAutoGrid->setChecked(model.isAutoGrid());

  m_hLines->setValue(model.getGridLinesNumber(GraphParametersModel::GridSide::X_SIDE));

  auto xMin = model.getGridLinesOrigin(GraphParametersModel::GridSide::X_SIDE);
  setDoubleSpinBoxValue(*m_hMin, xMin);

  auto xMax = model.getGridLinesEnd(GraphParametersModel::GridSide::X_SIDE);
  setDoubleSpinBoxValue(*m_hMax, xMax);

  m_vLines->setValue(model.getGridLinesNumber(GraphParametersModel::GridSide::Y_SIDE));

  auto yMin = model.getGridLinesOrigin(GraphParametersModel::GridSide::Y_SIDE);
  setDoubleSpinBoxValue(*m_vMin, yMin);

  auto yMax = model.getGridLinesEnd(GraphParametersModel::GridSide::Y_SIDE);
  setDoubleSpinBoxValue(*m_vMax, yMax);

  if(m_isAutoGrid->isChecked()) {
    setManualGridControlsEnabled(false);
  } else {
    setManualGridControlsEnabled(true);
  }
}

void GraphParametersWidget::setDoubleSpinBoxValue(QDoubleSpinBox& box, double value) {
  box.setValue(value);

  auto order = Utilities::orderOfTen(value);
  if(order < 0) {
    box.setDecimals(std::abs(order) + 2);
    box.setSingleStep(std::pow(10.0, -box.decimals()));
  }
}

void GraphParametersWidget::updateGraphData(const GraphParametersModel&) {

}

GraphWidget* GraphParametersWidget::getCurrentGraph() const {
  auto graphIdx = m_graphSelector->currentData();

  if(graphIdx.isValid()) {
    return m_graphs.at(graphIdx.toUInt());
  } else {
    Logger::log(GuiMessage::ERROR_INVALID_GRAPH_SELECTOR_DATA,
                m_graphSelector->currentIndex(),
                m_graphSelector->currentText().toStdString());

    return nullptr;
  }
}

void GraphParametersWidget::graphSelectorChanged(int index) {
  if(index == -1) {
    // In case when QComboBox is cleared
    return;
  }

  GraphWidget* graph = nullptr;
  size_t idx = static_cast<size_t>(index);

  if(idx < m_graphs.size()) {
    graph = m_graphs.at(idx);
    updateGraphParametersView(graph);
  } else {
    Logger::log(GuiMessage::ERROR_INVALID_GRAPH_SELECTOR_INDEX, index);
  }
}

void GraphParametersWidget::autoGridChanged(int state) {
  auto graph = getCurrentGraph();
  if(graph) {
    GraphParametersModel model(*graph);
    model.setAutoGrid(state == Qt::Checked);

    if(state == Qt::Checked) {
      graph->repaint();
    }

    updateGraphParametersView(graph);
  }
}

void GraphParametersWidget::colorControlRequested(ColorControl control) {
  const QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");

  if(!color.isValid()) {
    Logger::log(GuiMessage::ERROR_INVALID_COLOR);
    return;
  }

  auto graph = getCurrentGraph();
  if(!graph) {
    return;
  }

  GraphParametersModel model(*graph);
  QPushButton* buttonControl = nullptr;

  switch(control) {
    case ColorControl::BACKGROUND_COLOR:
      model.setBackgroundColor(color);
      buttonControl = m_bgColorButton;
      break;

    case ColorControl::GRID_LINES_COLOR:
      model.setGridLinesColor(color);
      buttonControl = m_gridColors;
      break;

    case ColorControl::GRAPH_DATA_LINE_COLOR:
      break;
  }

  graph->repaint();

  if(!buttonControl) {
    Logger::log(GuiMessage::ERROR_INVALID_BUTTON_COLOR_CONTROL);
    return;
  }

  buttonControl->setPalette(QPalette(color));
  buttonControl->setAutoFillBackground(true);
}

void GraphParametersWidget::updateGridLinesRange(double value, SideControl side) {
  auto graph = getCurrentGraph();
  if(!graph) {
    return;
  }

  GraphParametersModel model(*graph);

  switch(side) {
    case SideControl::HORIZONTAL_MIN:
      model.setGridLinesOrigin(GraphParametersModel::GridSide::X_SIDE, value);
      break;

    case SideControl::HORIZONTAL_MAX:
      model.setGridLinesEnd(GraphParametersModel::GridSide::X_SIDE, value);
      break;

    case SideControl::VERTICAL_MIN:
      model.setGridLinesOrigin(GraphParametersModel::GridSide::Y_SIDE, value);
      break;

    case SideControl::VERTICAL_MAX:
      model.setGridLinesEnd(GraphParametersModel::GridSide::Y_SIDE, value);
      break;
  }

  graph->repaint();
}

void GraphParametersWidget::updateGridLinesNumber(int value, bool isHorizontal) {
  auto graph = getCurrentGraph();
  if(!graph) {
    return;
  }

  GraphParametersModel model(*graph);
  if(isHorizontal) {
    model.setGridLinesNumber(GraphParametersModel::GridSide::X_SIDE, value);
  } else {
    model.setGridLinesNumber(GraphParametersModel::GridSide::Y_SIDE, value);
  }

  graph->repaint();
}

} // namespace Gui
} // namespace PowerLab

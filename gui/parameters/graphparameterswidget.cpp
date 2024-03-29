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
#include <QLineEdit>

#include "graphparameterswidget.h"
#include "graphs/graphwidget.h"
#include "graphs/graphparametersmodel.h"
#include "utils/mathutils.h"
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
  addHorizontalSeparator(m_grid->rowCount());
  createPlotScaleControls();
  createPlotColorControls();
  addHorizontalSeparator(m_grid->rowCount());
  createPlotGridControls();
  addHorizontalSeparator(m_grid->rowCount());
  createGraphDataControls();
  addHorizontalSeparator(m_grid->rowCount());
  createGraphReferenceControls();

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

  auto rowIdx = m_grid->rowCount();
  m_grid->addWidget(graphSelectorLabel, rowIdx++, 0, 1, -1);
  m_grid->addWidget(m_graphSelector, rowIdx++, 0, 1, -1);
}

void GraphParametersWidget::createPlotScaleControls() {
  auto rowIdx = m_grid->rowCount();

  addLabel(tr("Plot Hmin"), rowIdx, 0);
  m_hScaleMin = new QDoubleSpinBox;
  m_hScaleMin->setRange(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max());
  connect(m_hScaleMin, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          [this](double value){
    this->updatePlotScaleRange(value, SideControl::HORIZONTAL_MIN);
  });

  m_grid->addWidget(m_hScaleMin, rowIdx++, 1);
  m_layoutElements.push_back(m_hScaleMin);

  addLabel(tr("Plot Hmax"), rowIdx, 0);
  m_hScaleMax = new QDoubleSpinBox;
  m_hScaleMax->setRange(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max());
  connect(m_hScaleMax, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          [this](double value){
    this->updatePlotScaleRange(value, SideControl::HORIZONTAL_MAX);
  });

  m_grid->addWidget(m_hScaleMax, rowIdx++, 1);
  m_layoutElements.push_back(m_hScaleMax);

  addLabel(tr("Plot Vmin"), rowIdx, 0);
  m_vScaleMin = new QDoubleSpinBox;
  m_vScaleMin->setRange(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max());
  connect(m_vScaleMin, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          [this](double value){
    this->updatePlotScaleRange(value, SideControl::VERTICAL_MIN);
  });

  m_grid->addWidget(m_vScaleMin, rowIdx++, 1);
  m_layoutElements.push_back(m_vScaleMin);

  addLabel(tr("Plot Vmax"), rowIdx, 0);
  m_vScaleMax = new QDoubleSpinBox;
  m_vScaleMax->setRange(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max());
  connect(m_vScaleMax, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          [this](double value){
    this->updatePlotScaleRange(value, SideControl::VERTICAL_MAX);
  });

  m_grid->addWidget(m_vScaleMax, rowIdx++, 1);
  m_layoutElements.push_back(m_vScaleMax);
}

void GraphParametersWidget::createPlotColorControls() {
  m_bgColorButton = new QPushButton(tr("Background color"));
  connect(m_bgColorButton, &QPushButton::clicked, [this](bool /*Not interested*/){
    this->colorControlRequested(ColorControl::BACKGROUND_COLOR);
  });

  auto rowIdx = m_grid->rowCount();
  m_grid->addWidget(m_bgColorButton, rowIdx, 0);

  m_gridColor = new QPushButton(tr("Grid color"));
  connect(m_gridColor, &QPushButton::clicked, [this](bool /*Not interested*/){
    this->colorControlRequested(ColorControl::GRID_LINES_COLOR);
  });

  m_grid->addWidget(m_gridColor, rowIdx++, 1);

  m_layoutElements.push_back(m_bgColorButton);
  m_layoutElements.push_back(m_gridColor);
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

  auto rowIdx = m_grid->rowCount();
  m_grid->addWidget(m_isAutoGrid, rowIdx++, 0, 1, -1);
  m_layoutElements.push_back(m_isAutoGrid);

  addLabel(tr("Grid Hmin"), rowIdx, 0);
  m_hGridMin = new QDoubleSpinBox;
  m_hGridMin->setRange(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max());
  connect(m_hGridMin, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          [this](double value){
    this->updateGridLinesRange(value, SideControl::HORIZONTAL_MIN);
  });

  m_grid->addWidget(m_hGridMin, rowIdx++, 1);
  m_manualGridControls.push_back(m_hGridMin);

  addLabel(tr("Grid Hmax"), rowIdx, 0);
  m_hGridMax = new QDoubleSpinBox;
  m_hGridMax->setRange(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max());
  connect(m_hGridMax, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          [this](double value){
    this->updateGridLinesRange(value, SideControl::HORIZONTAL_MAX);
  });

  m_grid->addWidget(m_hGridMax, rowIdx++, 1);
  m_manualGridControls.push_back(m_hGridMax);

  addLabel(tr("Grid Hlines"), rowIdx, 0);
  m_hGridLines = new QSpinBox;
  m_hGridLines->setRange(0, 40);
  m_hGridLines->setSingleStep(1);
  connect(m_hGridLines, QOverload<int>::of(&QSpinBox::valueChanged),
          [this](int value){
    this->updateGridLinesNumber(value, true);
  });

  m_grid->addWidget(m_hGridLines, rowIdx++, 1);
  m_manualGridControls.push_back(m_hGridLines);

  addLabel(tr("Grid Vmin"), rowIdx, 0);
  m_vGridMin = new QDoubleSpinBox;
  m_vGridMin->setRange(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max());
  connect(m_vGridMin, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          [this](double value){
    this->updateGridLinesRange(value, SideControl::VERTICAL_MIN);
  });

  m_grid->addWidget(m_vGridMin, rowIdx++, 1);
  m_manualGridControls.push_back(m_vGridMin);

  addLabel(tr("Grid Vmax"), rowIdx, 0);
  m_vGridMax = new QDoubleSpinBox;
  m_vGridMax->setRange(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max());
  connect(m_vGridMax, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          [this](double value){
    this->updateGridLinesRange(value, SideControl::VERTICAL_MAX);
  });

  m_grid->addWidget(m_vGridMax, rowIdx++, 1);
  m_manualGridControls.push_back(m_vGridMax);

  addLabel(tr("Grid Vlines"), rowIdx, 0);
  m_vGridLines = new QSpinBox;
  m_vGridLines->setRange(0, 40);
  m_vGridLines->setSingleStep(1);
  connect(m_vGridLines, QOverload<int>::of(&QSpinBox::valueChanged),
          [this](int value){
    this->updateGridLinesNumber(value, false);
  });

  m_grid->addWidget(m_vGridLines, rowIdx++, 1);
  m_manualGridControls.push_back(m_vGridLines);
}

void GraphParametersWidget::setManualGridControlsEnabled(bool enabled) {
  for(auto item : m_manualGridControls) {
    item->setEnabled(enabled);
  }
}

void GraphParametersWidget::createGraphDataControls() {
  auto rowIdx = m_grid->rowCount();

  m_graphDataSelector = new QComboBox;
  m_graphDataName = new QLineEdit;
  m_graphDataUnits = new QLineEdit;
  m_graphDataLineColor = new QPushButton(tr("Line color"));
  m_graphDataLineWidth = new QSpinBox;
  m_graphDataLineWidth->setRange(1, 10);
  m_graphDataLineWidth->setPrefix(tr("Line width: "));

  connect(m_graphDataSelector, QOverload<int>::of(&QComboBox::currentIndexChanged),
          this, &GraphParametersWidget::graphDataSelectorChanged);

  connect(m_graphDataLineColor, &QPushButton::clicked, [this](bool /*Not interested*/){
    this->colorControlRequested(ColorControl::GRAPH_DATA_LINE_COLOR,
                                m_graphDataSelector->currentIndex());
  });

  connect(m_graphDataName, &QLineEdit::textEdited, [this](const QString& text){
    auto idx = this->m_graphDataSelector->currentIndex();
    this->updateGraphDataName(idx, text);
  });

  connect(m_graphDataUnits, &QLineEdit::textEdited, [this](const QString& text){
    auto idx = this->m_graphDataSelector->currentIndex();
    this->updateGraphDataUnits(idx, text);
  });

  connect(m_graphDataLineWidth, QOverload<int>::of(&QSpinBox::valueChanged),
          [this](int value){
    auto idx = this->m_graphDataSelector->currentIndex();
    this->updateGraphDataLineWidth(idx, value);
  });

  m_grid->addWidget(m_graphDataSelector, rowIdx++, 0, 1, -1);
  m_grid->addWidget(m_graphDataLineColor, rowIdx, 0);
  m_grid->addWidget(m_graphDataLineWidth, rowIdx++, 1);

  addLabel(tr("Scale V name"), rowIdx, 0);
  m_grid->addWidget(m_graphDataName, rowIdx++, 1);

  addLabel(tr("Scale V units"), rowIdx, 0);
  m_grid->addWidget(m_graphDataUnits, rowIdx++, 1);

  m_layoutElements.push_back(m_graphDataSelector);
  m_layoutElements.push_back(m_graphDataName);
  m_layoutElements.push_back(m_graphDataUnits);
  m_layoutElements.push_back(m_graphDataLineWidth);
  m_layoutElements.push_back(m_graphDataLineColor);
}

void GraphParametersWidget::createGraphReferenceControls() {
  auto rowIdx = m_grid->rowCount();

  m_graphReferenceName = new QLineEdit;
  m_graphReferenceUnits = new QLineEdit;

  addLabel(tr("Scale H name"), rowIdx, 0);
  m_grid->addWidget(m_graphReferenceName, rowIdx++, 1);

  addLabel(tr("Scale H units"), rowIdx, 0);
  m_grid->addWidget(m_graphReferenceUnits, rowIdx++, 1);

  connect(m_graphReferenceName, &QLineEdit::textEdited, [this](const QString& text){
    this->updateGraphDataName(GRAPH_DATA_REFERENCE_INDEX, text);
  });

  connect(m_graphReferenceUnits, &QLineEdit::textEdited, [this](const QString& text){
    this->updateGraphDataUnits(GRAPH_DATA_REFERENCE_INDEX, text);
  });

  m_layoutElements.push_back(m_graphReferenceName);
  m_layoutElements.push_back(m_graphReferenceUnits);
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

  m_blockModelUpdateSignals = true;

  GraphParametersModel model(*graph);

  updatePlotScale(model);
  updateGridColors(model);
  updateGridLines(model);
  updateGraphData(model);

  m_blockModelUpdateSignals = false;
}

void GraphParametersWidget::updatePlotScale(const GraphParametersModel& model) {
  auto plotArea = model.getValueBounds();

  auto xMin = plotArea.left();
  setDoubleSpinBoxValue(*m_hScaleMin, xMin);

  auto xMax = plotArea.right();
  setDoubleSpinBoxValue(*m_hScaleMax, xMax);

  auto yMin = plotArea.top();
  setDoubleSpinBoxValue(*m_vScaleMin, yMin);

  auto yMax = plotArea.bottom();
  setDoubleSpinBoxValue(*m_vScaleMax, yMax);
}

void GraphParametersWidget::updateGridColors(const GraphParametersModel& model) {
  m_bgColorButton->setPalette(model.getBackgroundColor());
  m_bgColorButton->setAutoFillBackground(true);

  m_gridColor->setPalette((model.getGridLinesColor()));
  m_gridColor->setAutoFillBackground(true);
}

void GraphParametersWidget::updateGridLines(const GraphParametersModel& model) {
  m_isAutoGrid->setChecked(model.isAutoGrid());

  m_hGridLines->setValue(model.getGridLinesNumber(GraphParametersModel::GridSide::X_SIDE));

  auto xMin = model.getGridLinesOrigin(GraphParametersModel::GridSide::X_SIDE);
  setDoubleSpinBoxValue(*m_hGridMin, xMin);

  auto xMax = model.getGridLinesEnd(GraphParametersModel::GridSide::X_SIDE);
  setDoubleSpinBoxValue(*m_hGridMax, xMax);

  m_vGridLines->setValue(model.getGridLinesNumber(GraphParametersModel::GridSide::Y_SIDE));

  auto yMin = model.getGridLinesOrigin(GraphParametersModel::GridSide::Y_SIDE);
  setDoubleSpinBoxValue(*m_vGridMin, yMin);

  auto yMax = model.getGridLinesEnd(GraphParametersModel::GridSide::Y_SIDE);
  setDoubleSpinBoxValue(*m_vGridMax, yMax);

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

void GraphParametersWidget::updateGraphData(const GraphParametersModel& model) {
  auto graphSize = model.getGraphNumber();

  m_graphDataSelector->clear();
  for(GraphParametersModel::GraphDataIdx idx = 0; idx < graphSize; idx++) {
    auto graphDataName = model.getGraphName(idx);
    m_graphDataSelector->addItem(QString::fromStdString(graphDataName), QVariant::fromValue(idx));
  }

  // @TODO: Keep track of the last graph data index
  updateGraphDataSelected(model, 0);

  m_graphReferenceName->setText(QString::fromStdString(model.getReferenceName()));
  m_graphReferenceUnits->setText(QString::fromStdString(model.getReferenceUnits()));
}

void GraphParametersWidget::updateGraphDataSelected(const GraphParametersModel& model, int graphDataIdx) {
  auto idx = static_cast<GraphParametersModel::GraphDataIdx>(graphDataIdx);

  m_graphDataName->setText(QString::fromStdString(model.getGraphName(idx)));
  m_graphDataUnits->setText(QString::fromStdString(model.getGraphUnits(idx)));

  m_graphDataLineColor->setPalette(model.getGraphColor(idx));
  m_graphDataLineColor->setAutoFillBackground(true);

  m_graphDataLineWidth->setValue(model.getLineWidth(idx));
}

GraphWidget* GraphParametersWidget::getCurrentGraph() const {
  auto graphIdx = m_graphSelector->currentData();

  if(graphIdx.isValid()) {
    return m_graphs.at(graphIdx.toUInt());
  } else {
    Logger::log(Message::ERROR_INVALID_GRAPH_SELECTOR_DATA,
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
    Logger::log(Message::ERROR_INVALID_GRAPH_SELECTOR_INDEX, index);
  }
}

void GraphParametersWidget::graphDataSelectorChanged(int index) {
  if(index == -1) {
    // In case when QComboBox is cleared
    return;
  }

  auto graph = getCurrentGraph();
  if(graph) {
    auto model = GraphParametersModel(*graph);
    auto graphDataIdx = static_cast<GraphParametersModel::GraphDataIdx>(m_graphDataSelector->currentIndex());

    if(graphDataIdx >= model.getGraphNumber()) {
      Logger::log(Message::ERROR_INVALID_GRAPH_DATA_INDEX, graphDataIdx, model.getGraphNumber());
      return;
    }

    updateGraphDataSelected(model, m_graphDataSelector->currentIndex());
  }
}

void GraphParametersWidget::autoGridChanged(int state) {
  auto graph = getCurrentGraph();
  if(graph && !m_blockModelUpdateSignals) {
    GraphParametersModel model(*graph);
    model.setAutoGrid(state == Qt::Checked);

    if(state == Qt::Checked) {
      graph->repaint();
    }

    updateGraphParametersView(graph);
  }
}

void GraphParametersWidget::colorControlRequested(ColorControl control, int idx) {
  const QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");

  if(!color.isValid()) {
    Logger::log(Message::ERROR_INVALID_COLOR);
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
      buttonControl = m_gridColor;
      break;

    case ColorControl::GRAPH_DATA_LINE_COLOR:
      auto graphDataIdx = static_cast<GraphParametersModel::GraphDataIdx>(idx);
      if(graphDataIdx >= model.getGraphNumber()) {
        Logger::log(Message::ERROR_INVALID_GRAPH_DATA_INDEX, graphDataIdx, model.getGraphNumber());
        return;
      }
      model.setGraphColor(graphDataIdx, color);
      buttonControl = m_graphDataLineColor;
      break;
  }

  graph->repaint();

  if(!buttonControl) {
    Logger::log(Message::ERROR_INVALID_BUTTON_COLOR_CONTROL);
    return;
  }

  buttonControl->setPalette(QPalette(color));
  buttonControl->setAutoFillBackground(true);
}

void GraphParametersWidget::updatePlotScaleRange(double value, SideControl side) {
  auto graph = getCurrentGraph();
  if(!graph || m_blockModelUpdateSignals) {
    return;
  }

  GraphParametersModel model(*graph);
  auto plotArea = model.getValueBounds();

  switch(side) {
    case SideControl::HORIZONTAL_MIN:
      plotArea.setLeft(value);
      break;

    case SideControl::HORIZONTAL_MAX:
      plotArea.setRight(value);
      break;

    case SideControl::VERTICAL_MIN:
      plotArea.setTop(value);
      break;

    case SideControl::VERTICAL_MAX:
      plotArea.setBottom(value);
      break;
  }

  model.setValueBounds(plotArea);
  graph->repaint();
}

void GraphParametersWidget::updateGridLinesRange(double value, SideControl side) {
  auto graph = getCurrentGraph();
  if(!graph || m_blockModelUpdateSignals) {
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
  if(!graph || m_blockModelUpdateSignals) {
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

void GraphParametersWidget::updateGraphDataLineWidth(int index, int width) {
  auto graph = getCurrentGraph();
  if(!graph || m_blockModelUpdateSignals) {
    return;
  }

  GraphParametersModel model(*graph);

  auto graphDataIdx = static_cast<GraphParametersModel::GraphDataIdx>(index);
  if(graphDataIdx >= model.getGraphNumber()) {
    Logger::log(Message::ERROR_INVALID_GRAPH_DATA_INDEX, graphDataIdx, model.getGraphNumber());
    return;
  }

  model.setLineWidth(graphDataIdx, width);
  graph->repaint();
}

void GraphParametersWidget::updateGraphDataName(int index, QString text) {
  auto graph = getCurrentGraph();
  if(!graph || m_blockModelUpdateSignals) {
    return;
  }

  GraphParametersModel model(*graph);

  if(index == GRAPH_DATA_REFERENCE_INDEX) {
    model.setReferenceName(text.toStdString());
  } else {
    auto graphDataIdx = static_cast<GraphParametersModel::GraphDataIdx>(index);
    if(graphDataIdx >= model.getGraphNumber()) {
      Logger::log(Message::ERROR_INVALID_GRAPH_DATA_INDEX, graphDataIdx, model.getGraphNumber());
      return;
    }

    model.setGraphName(graphDataIdx, text.toStdString());
  }

  graph->repaint();
}

void GraphParametersWidget::updateGraphDataUnits(int index, QString text) {
  auto graph = getCurrentGraph();
  if(!graph || m_blockModelUpdateSignals) {
    return;
  }

  GraphParametersModel model(*graph);

  if(index == GRAPH_DATA_REFERENCE_INDEX) {
    model.setReferenceUnits(text.toStdString());
  } else {
    auto graphDataIdx = static_cast<GraphParametersModel::GraphDataIdx>(index);
    if(graphDataIdx >= model.getGraphNumber()) {
      Logger::log(Message::ERROR_INVALID_GRAPH_DATA_INDEX, graphDataIdx, model.getGraphNumber());
      return;
    }

    model.setGraphUnits(graphDataIdx, text.toStdString());
  }

  graph->repaint();
}

} // namespace Gui
} // namespace PowerLab

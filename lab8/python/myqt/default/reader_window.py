from myqt.default.default_window import *

import analyze.tab_func as tf


class ReaderWindow(Window):
    def __init__(self, parent_window: Window | None):
        super().__init__(parent_window)

        # Define available windows to switch

        # Define available button to click

        submit_button: Button = Button("Начать генерацию файлов")
        submit_button.on_click(self.read_info)

        # Define inputs
        self.input_left = QLineEdit()
        self.input_left.setFixedWidth(150)
        self.input_left.setText("-1")

        self.input_right = QLineEdit()
        self.input_right.setFixedWidth(150)
        self.input_right.setText("1")

        self.input_exp_cnt = QLineEdit()
        self.input_exp_cnt.setFixedWidth(150)
        self.input_exp_cnt.setText("1")

        self.input_step = QLineEdit()
        self.input_step.setFixedWidth(150)
        self.input_step.setText("1")

        # Define labels
        self.label_left = QLabel(self)
        self.label_left.setText('Left:')

        self.label_right = QLabel(self)
        self.label_right.setText('Right:')

        self.label_cnt = QLabel(self)
        self.label_cnt.setText('Cnt:')

        self.label_step = QLabel(self)
        self.label_step.setText('Step:')

        self.label_grid = QLabel(self)
        self.label_grid.setText('Сетка:')

        # Define checkboxes
        self.check_1 = QCheckBox()
        self.check_1.setText("y = 3*x-cos(x)-1")
        self.check_1.setChecked(True)

        self.check_2 = QCheckBox()
        self.check_2.setText("y= x^3-sign(x)*x^2+6*x+3")
        self.check_2.setChecked(True)

        self.combo_grid = QComboBox(self)
        self.combo_grid.addItem('Равномерная')
        self.combo_grid.addItem('Чебышевская')
        self.combo_grid.addItem('Сгущение в 0')

        # Add widgets to layout
        self.layout.addWidget(self.check_1, 1, 1, Qt.AlignmentFlag.AlignCenter)
        self.layout.addWidget(self.check_2, 2, 1, Qt.AlignmentFlag.AlignCenter)

        self.layout.addWidget(self.input_left, 3, 1, Qt.AlignmentFlag.AlignCenter)
        self.layout.addWidget(self.input_right, 4, 1, Qt.AlignmentFlag.AlignCenter)
        self.layout.addWidget(self.input_exp_cnt, 5, 1, Qt.AlignmentFlag.AlignCenter)
        self.layout.addWidget(self.input_step, 6, 1, Qt.AlignmentFlag.AlignCenter)

        self.layout.addWidget(self.combo_grid, 7, 1, Qt.AlignmentFlag.AlignCenter)

        self.layout.addWidget(self.label_left, 3, 0, Qt.AlignmentFlag.AlignRight)
        self.layout.addWidget(self.label_right, 4, 0, Qt.AlignmentFlag.AlignRight)
        self.layout.addWidget(self.label_cnt, 5, 0, Qt.AlignmentFlag.AlignRight)
        self.layout.addWidget(self.label_step, 6, 0, Qt.AlignmentFlag.AlignRight)
        self.layout.addWidget(self.label_grid, 7, 0, Qt.AlignmentFlag.AlignRight)

        self.layout.addWidget(submit_button, 8, 1, 10, 1, Qt.AlignmentFlag.AlignCenter)

    def read_info(self):
        ...

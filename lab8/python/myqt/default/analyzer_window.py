from myqt.default.default_window import *

from analyze.p3 import analyze


class AnalyzerWindow(Window):
    def __init__(self, parent_window: Window | None):
        super().__init__(parent_window)

        # Define available windows to switch

        # Define available button to click
        submit_button: Button = Button("Начать анализ")
        submit_button.on_click(self.analyze_results)

        # Define inputs
        self.input_left = QLineEdit()
        self.input_left.setFixedWidth(150)
        self.input_left.setText("-1")

        self.input_right = QLineEdit()
        self.input_right.setFixedWidth(150)
        self.input_right.setText("1")

        # Define labels
        self.label_left = QLabel(self)
        self.label_left.setText('Left:')

        self.label_right = QLabel(self)
        self.label_right.setText('Right:')

        self.check_1 = QCheckBox()
        self.check_1.setText("y = 3*x-cos(x)-1")
        self.check_1.setChecked(True)
        self.check_2 = QCheckBox()
        self.check_2.setText("y= x^3-sign(x)*x^2+6*x+3")
        self.check_2.setChecked(True)

        # Add widgets to layout
        self.layout.addWidget(self.check_1, 1, 1, Qt.AlignmentFlag.AlignCenter)
        self.layout.addWidget(self.check_2, 2, 1, Qt.AlignmentFlag.AlignCenter)

        self.layout.addWidget(self.input_left, 3, 1, Qt.AlignmentFlag.AlignCenter)
        self.layout.addWidget(self.input_right, 4, 1, Qt.AlignmentFlag.AlignCenter)

        self.layout.addWidget(self.label_left, 3, 0, Qt.AlignmentFlag.AlignCenter)
        self.layout.addWidget(self.label_right, 4, 0, Qt.AlignmentFlag.AlignCenter)

        self.layout.addWidget(submit_button, 8, 1, 10, 1, Qt.AlignmentFlag.AlignCenter)

    def analyze_results(self):
        ...

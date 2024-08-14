from PyQt6.QtWidgets import *
from myqt.main_window import MainWindow

app: QApplication = QApplication([])
window = MainWindow()
window.show()
app.exec()

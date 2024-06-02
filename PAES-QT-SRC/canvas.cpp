#include <QtWidgets>

#include "canvas.h"
#include "scribblearea.h"
#include "mainwindow.h"
#include "login.h"
#include "userinfo.h"
#include <chrono>
#include <sstream>
#include <iomanip>

std::string getFormattedDateTime() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();

}

QPushButton *backButton;

// MainWindow constructor
Canvas::Canvas()
{
    // Create the ScribbleArea widget and make it
    // the central widget
    scribbleArea = new ScribbleArea;
    setCentralWidget(scribbleArea);
    connect(scribbleArea, &ScribbleArea::rightMouseClicked, this, &Canvas::savePng);

    // Create actions and menus
    createActions();
    createMenus();

    // Set the title
    setWindowTitle(tr("Bakıcı Çağır"));

    // Size the app
    resize(500, 500);
    backButton = new QPushButton(tr("<-"), this);
    backButton->setStyleSheet(
        "QPushButton {"
        "   color: black;"              // Ensure text color is black
        "   background-color: white;"   // Button background is white
        "   border-style: none;"        // No border for a flat look
        "   border: 1px solid #8f8f91;"
        "   border-radius: 10px;"
        "   padding: 5px 10px;"         // Adjust padding to match the visual weight
        "   font-size: 16px;"           // Ensure font size is sufficiently large
        "}"
        );
    connect(backButton, &QPushButton::clicked, this, &Canvas::handleBackButton);
    backButton->setFixedSize(40, 40);  // Set a fixed size for the button
    backButton->setGeometry(5, 25, backButton->width(), backButton->height());  // X, Y, Width, Height
    backButton->setCursor(Qt::PointingHandCursor);

    // Layout for the button, place it at the top or another location
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(backButton);
    layout->addStretch();  // Ensures the button stays at the top
    setLayout(layout);

}

void Canvas::handleBackButton() {

    if (backButton) {
        backButton->setEnabled(false);
    }

    //For example, just close this window
    MainWindow* main2 = new MainWindow();
    main2->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    main2->showFullScreen();
    // Process pending events to ensure the new window is rendered
    QApplication::processEvents();

    // Then hide the current window
    this->hide();

    if (backButton) {
        backButton->setEnabled(true);
    }
}

// User tried to close the app
void Canvas::closeEvent(QCloseEvent *event)
{
    // If they try to close maybeSave() returns true
    // if no changes have been made and the app closes
    if (maybeSave()) {
        event->accept();
    } else {

        // If there have been changes ignore the event
        event->ignore();
    }

//    event->ignore();
}

// Check if the current image has been changed and then
// open a dialog to open a file
void Canvas::open()
{
    // Check if changes have been made since last save
    // maybeSave() returns true if no changes have been made
    if (maybeSave()) {

        // Get the file to open from a dialog
        // tr sets the window title to Open File
        // QDir opens the current dirctory
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Dosya aç"), QDir::currentPath());

        // If we have a file name load the image and place
        // it in the scribbleArea
        if (!fileName.isEmpty())
            scribbleArea->openImage(fileName);
    }
}

// Called when the user clicks Save As in the menu
void Canvas::save()
{
    // A QAction represents the action of the user clicking
    QAction *action = qobject_cast<QAction *>(sender());

    // Stores the array of bytes of the users data
    QByteArray fileFormat = action->data().toByteArray();

    // Pass it to be saved
    saveFile(fileFormat);
}

// Opens a dialog to change the pen color
void Canvas::penColor()
{
    // Store the chosen color from the dialog
    QColor newColor = QColorDialog::getColor(scribbleArea->penColor());

    // If a valid color set it
    if (newColor.isValid())
        scribbleArea->setPenColor(newColor);
}

// Opens a dialog that allows the user to change the pen width
void Canvas::penWidth()
{
    // Stores button value
    bool ok;

    // tr("Scribble") is the title
    // the next tr is the text to display
    // Get the current pen width
    // Define the min, max, step and ok button
    int newWidth = QInputDialog::getInt(this, tr("Çizim"),
                                        tr("Kalem Büyüklüğü:"),
                                        scribbleArea->penWidth(),
                                        1, 50, 1, &ok);
    // Change the pen width
    if (ok)
        scribbleArea->setPenWidth(newWidth);
}

// Open an about dialog
void Canvas::about()
{
    // Window title and text to display
    QMessageBox::about(this, tr("Çizim Hakkında"),
                       tr("<p>The <b>Scribble</b> example is awesome</p>"));
}

// Define menu actions that call functions
void Canvas::createActions()
{
    // Create the action tied to the menu
    openAct = new QAction(tr("&Aç..."), this);

    // Define the associated shortcut key
    openAct->setShortcuts(QKeySequence::Open);

    // Tie the action to MainWindow::open()
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    // Get a list of the supported file formats
    // QImageWriter is used to write images to files
    foreach (QByteArray format, QImageWriter::supportedImageFormats()) {
        if (QString(format).compare("png", Qt::CaseInsensitive) == 0) {
            QString text = tr("%1...").arg(QString(format).toUpper());
            QAction *action = new QAction(text, this);
            action->setData(format);
            connect(action, &QAction::triggered, this, &Canvas::savePng);  // Direct connection to savePng()
            saveAsActs.append(action);
        }
    }

    // Create print action and tie to MainWindow::print()
    printAct = new QAction(tr("&Yazdır..."), this);
    connect(printAct, SIGNAL(triggered()), scribbleArea, SLOT(print()));

    // Create exit action and tie to MainWindow::close()
    exitAct = new QAction(tr("&Çık"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    // Create pen color action and tie to MainWindow::penColor()
    penColorAct = new QAction(tr("&Kalem rengi..."), this);
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

    // Create pen width action and tie to MainWindow::penWidth()
    penWidthAct = new QAction(tr("&Kalem kalınlığı..."), this);
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

    // Create clear screen action and tie to MainWindow::clearImage()
    clearScreenAct = new QAction(tr("&Ekranı temizle"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()),
            scribbleArea, SLOT(clearImage()));

    // Create about action and tie to MainWindow::about()
    aboutAct = new QAction(tr("&Hakkında"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    // Create about Qt action and tie to MainWindow::aboutQt()
    aboutQtAct = new QAction(tr("&QT hakkında"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

// Create the menubar
void Canvas::createMenus()
{
    // Create Save As option and the list of file types
    saveAsMenu = new QMenu(tr("&Kaydet"), this);
    foreach (QAction *action, saveAsActs)
    saveAsMenu->addAction(action);


    // Attach all actions to File
    fileMenu = new QMenu(tr("&Dosya"), this);
    //fileMenu->addAction(openAct);
    fileMenu->addMenu(saveAsMenu);
    //fileMenu->addAction(printAct);
    //fileMenu->addSeparator();
    //fileMenu->addAction(exitAct);

    // Attach all actions to Options
    optionMenu = new QMenu(tr("&Ayarlar"), this);
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);

    // Attach all actions to Help
    helpMenu = new QMenu(tr("&Yardım"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    // Add menu items to the menubar
    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
    menuBar()->addMenu(helpMenu);
}

bool Canvas::maybeSave()
{
    // Check for changes since last save
    /*if (scribbleArea->isModified()) {
        QMessageBox::StandardButton ret;

        // Scribble is the title
        // Add text and the buttons
        ret = QMessageBox::warning(this, tr("Scribble"),
                                   tr("Bu görselde değişiklikler yapıldı.\n"
                                      "Değişiklikleri kaydetmek ister misin?"),
                                   QMessageBox::Save | QMessageBox::Discard
                                       | QMessageBox::Cancel);

        // If save button clicked call for file to be saved
        if (ret == QMessageBox::Save) {
            return saveFile("png");

            // If cancel do nothing
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }*/
    return false;
}

bool Canvas::saveFile(const QByteArray &fileFormat)
{
    // Define path, name and default file type
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    // Get selected file from dialog
    // Add the proper file formats and extensions
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    initialPath,
                                                    tr("%1 Files (*.%2);;All Files (*)")
                                                        .arg(QString::fromLatin1(fileFormat.toUpper()))
                                                        .arg(QString::fromLatin1(fileFormat)));

    // If no file do nothing
    if (fileName.isEmpty()) {
        return false;
    } else {

        // Call for the file to be saved
        return scribbleArea->saveImage(fileName, fileFormat.constData());
    }
}

void Canvas::savePng(){

    QImage image = scribbleArea->getImage();  // Ensure you have this method in ScribbleArea

    QString filePath = QCoreApplication::applicationDirPath() + "/image.png";

    if (image.save(filePath, "PNG")){

        //QMessageBox::information(this, "Kaydet", "Görsel şuraya kaydedildi: " + filePath);

        // Create a QProcess object
        QProcess *process = new QProcess(this);

        // Build the path to the executable
        QString executablePath = QCoreApplication::applicationDirPath() + "/detect_shapes";

        // Start the executable
        process->start(executablePath);

        // Optionally, wait for the process to finish and check the result
        if (process->waitForFinished(-1)){ // Wait indefinitely until finished
            QString processOutput = process->readAllStandardOutput();
            int reply = QMessageBox::question(this, "Görüntü İşleme tamamlandı", "Sonuç: " + processOutput + "\nBakıcıya bildirim yolla?", QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes){
                // Code to execute if the user clicks 'Yes'

                try {
                    // Ensure there is existing patient data
                    auto patient_data = UserInfo::getInstance()->getPatientData();
                    bsoncxx::document::view pData = patient_data.view();
                    auto caregiver_str_id = pData["personal_caregiver"].get_string().value;

                    // Convert string to ObjectId
                    bsoncxx::oid caregiver_id(caregiver_str_id);

                    auto shape_triangle = pData["shape_triangle"].get_string().value;
                    auto shape_rectangle = pData["shape_rectangle"].get_string().value;
                    auto shape_circle = pData["shape_circle"].get_string().value;
                    auto shape_pentagon = pData["shape_pentagon"].get_string().value;
                    auto shape_line = pData["shape_line"].get_string().value;

                    // MongoDB connection using URI with proper credentials
                    auto client = mongocxx::client{mongocxx::uri{"mongodb+srv://berkeyilmaz:EZCYZoZiTQcIlaYn@paes-database.ufm3cd5.mongodb.net/?retryWrites=true&w=majority&appName=Paes-database"}};
                    auto collection = client["paes"]["caregivers"];

                    // Filter document to locate the existing patient
                    bsoncxx::builder::basic::document filter_builder{};
                    filter_builder.append(bsoncxx::builder::basic::kvp("_id", caregiver_id));  // Use ObjectId here

                    if(processOutput == "triangle"){

                        bsoncxx::builder::basic::document update_builder{};
                            update_builder.append(bsoncxx::builder::basic::kvp("$push", [&](bsoncxx::builder::basic::sub_document sub_doc) {
                                sub_doc.append(
                                    bsoncxx::builder::basic::kvp("notifications", [&](bsoncxx::builder::basic::sub_document sub_sub_doc) {
                                        sub_sub_doc.append(bsoncxx::builder::basic::kvp("room_number", pData["room_number"].get_string()));
                                        sub_sub_doc.append(bsoncxx::builder::basic::kvp("patient_number", pData["patient_number"].get_string()));
                                        sub_sub_doc.append(bsoncxx::builder::basic::kvp("request", pData["shape_triangle"].get_string()));
                                        sub_sub_doc.append(bsoncxx::builder::basic::kvp("requested_at", getFormattedDateTime()));
                                    })
                                    );
                            }));
                            collection.update_one(filter_builder.view(), update_builder.view());

                            QMessageBox::information(this,"İstek", "Hastabakıcıya bildirim başarıyla gönderildi.");

                    }else if(processOutput == "rectangle"){
                        bsoncxx::builder::basic::document update_builder{};
                        update_builder.append(bsoncxx::builder::basic::kvp("$push", [&](bsoncxx::builder::basic::sub_document sub_doc) {
                            sub_doc.append(
                                bsoncxx::builder::basic::kvp("notifications", [&](bsoncxx::builder::basic::sub_document sub_sub_doc) {
                                    sub_sub_doc.append(bsoncxx::builder::basic::kvp("room_number", pData["room_number"].get_string()));
                                    sub_sub_doc.append(bsoncxx::builder::basic::kvp("patient_number", pData["patient_number"].get_string()));
                                    sub_sub_doc.append(bsoncxx::builder::basic::kvp("request", shape_rectangle));
                                    sub_sub_doc.append(bsoncxx::builder::basic::kvp("requested_at", getFormattedDateTime()));
                                })
                                );
                        }));
                        collection.update_one(filter_builder.view(), update_builder.view());

                        QMessageBox::information(this, "İstek", "Hastabakıcıya bildirim başarıyla gönderildi.");

                    }else if(processOutput == "circle"){
                        bsoncxx::builder::basic::document update_builder{};
                        update_builder.append(bsoncxx::builder::basic::kvp("$push", [&](bsoncxx::builder::basic::sub_document sub_doc) {
                            sub_doc.append(
                                bsoncxx::builder::basic::kvp("notifications", [&](bsoncxx::builder::basic::sub_document sub_sub_doc) {
                                    sub_sub_doc.append(bsoncxx::builder::basic::kvp("room_number", pData["room_number"].get_string()));
                                    sub_sub_doc.append(bsoncxx::builder::basic::kvp("patient_number", pData["patient_number"].get_string()));
                                    sub_sub_doc.append(bsoncxx::builder::basic::kvp("request", shape_circle));
                                    sub_sub_doc.append(bsoncxx::builder::basic::kvp("requested_at", getFormattedDateTime()));
                                })
                                );
                        }));
                        collection.update_one(filter_builder.view(), update_builder.view());

                        QMessageBox::information(this, "İstek", "Hastabakıcıya bildirim başarıyla gönderildi.");

                    }else if(processOutput == "pentagon"){
                        bsoncxx::builder::basic::document update_builder{};
                        update_builder.append(bsoncxx::builder::basic::kvp("$push", [&](bsoncxx::builder::basic::sub_document sub_doc) {
                            sub_doc.append(
                                bsoncxx::builder::basic::kvp("notifications", [&](bsoncxx::builder::basic::sub_document sub_sub_doc) {
                                    sub_sub_doc.append(bsoncxx::builder::basic::kvp("room_number", pData["room_number"].get_string()));
                                    sub_sub_doc.append(bsoncxx::builder::basic::kvp("patient_number", pData["patient_number"].get_string()));
                                    sub_sub_doc.append(bsoncxx::builder::basic::kvp("request", shape_pentagon));
                                    sub_sub_doc.append(bsoncxx::builder::basic::kvp("requested_at", getFormattedDateTime()));
                                })
                                );
                        }));
                        collection.update_one(filter_builder.view(), update_builder.view());

                        QMessageBox::information(this, "İstek", "Hastabakıcıya bildirim başarıyla gönderildi.");

                    }else if(processOutput == "line"){
                        bsoncxx::builder::basic::document update_builder{};
                        update_builder.append(bsoncxx::builder::basic::kvp("$push", [&](bsoncxx::builder::basic::sub_document sub_doc) {
                            sub_doc.append(
                                bsoncxx::builder::basic::kvp("notifications", [&](bsoncxx::builder::basic::sub_document sub_sub_doc) {
                                    sub_sub_doc.append(bsoncxx::builder::basic::kvp("room_number", pData["room_number"].get_string()));
                                    sub_sub_doc.append(bsoncxx::builder::basic::kvp("patient_number", pData["patient_number"].get_string()));
                                    sub_sub_doc.append(bsoncxx::builder::basic::kvp("request", shape_line));
                                    sub_sub_doc.append(bsoncxx::builder::basic::kvp("requested_at", getFormattedDateTime()));
                                })
                                );
                        }));
                        collection.update_one(filter_builder.view(), update_builder.view());

                        QMessageBox::information(this,"İstek", "Hastabakıcıya bildirim başarıyla gönderildi.");

                    }else{
                        //do not update or send request
                        QMessageBox::information(this,"debug", "Obje bilinmiyor...");
                    }

                }
                catch (const mongocxx::exception& e) {
                    std::cerr << "MongoDB Error: " << e.what() << std::endl;
                    QMessageBox::critical(this, "Database Error", "Failed to update patient data. Please check your database connection and try again.");
                }

            } else {
                // Code to execute if the user clicks 'No'
                scribbleArea->clearImage();
            }

        } else {
            QMessageBox::critical(this, "Görüntü İşleme başarısız", "Program beklenmedik şekilde sonuçlandı.");
        }
    } else {
        QMessageBox::critical(this, "Kaydet", "Görsel kaydedilemedi.");
    }
}


/*
 * QDigiDoc4
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#pragma once

#include "common_enums.h"
#include "widgets/Item.h"

#include "SslCertificate.h"

#include <functional>
#include <QScrollArea>

namespace Ui {
class ItemList;
}

class QLabel;
class QSvgWidget;

class ItemList : public QScrollArea
{
	Q_OBJECT

public:
	explicit ItemList(QWidget *parent = {});
	~ItemList() override;

	void init(ria::qdigidoc4::ItemType itemType, const char *header);
	void addHeader(const char *label);
	void addHeaderWidget(Item *widget);
	void addWidget(Item *widget);
	virtual void clear();
	ria::qdigidoc4::ContainerState getState() const;
	bool hasItem(const std::function<bool(Item* const)> &cb);
	virtual void removeItem(int row);
	virtual void stateChange(ria::qdigidoc4::ContainerState state);

signals:
	void addAll();
	void addItem(int code);
	void addressSearch();
	void idChanged(const SslCertificate &cert);
	void keysSelected(QList<Item *> keys);
	void removed(int row);
	void search(const QString &term);

protected:
	void changeEvent(QEvent* event) override;
	bool eventFilter(QObject *o, QEvent *e) override;
	int index(Item *item) const;
	virtual void remove(Item *item);

	Ui::ItemList* ui;
	ria::qdigidoc4::ContainerState state = ria::qdigidoc4::UnsignedContainer;

private:
	QString addLabel();
	void addWidget(Item *widget, int index, QWidget *tabIndex = {});
	void setRecipientTooltip();

	QList<Item*> items;
	QLabel *header = nullptr;
	ria::qdigidoc4::ItemType itemType = ria::qdigidoc4::ItemAddress;
	const char *headerText = "";
	const char *listText = "";
	SslCertificate cert;

	friend class AddRecipients;
};
